#include "traffic_simulator.h"
#include "graph.h"
#include <QtMath>
#include <QDebug>
#include <QQueue>
#include <QRandomGenerator>
#include <QDateTime>

// Constructor
TrafficSimulator::TrafficSimulator(Graph* g, QObject* parent)
    : QObject(parent),
    graph(g),
    simulationSpeed(1.0),
    nextVehicleId(1),
    rerouteCooldown(30.0) // 30 seconds between reroutes
{
    connect(&timer, &QTimer::timeout, this, &TrafficSimulator::updateSimulation);
    timer.setInterval(50); // 20 updates/sec

    connect(&congestionTimer, &QTimer::timeout, this, &TrafficSimulator::updateCongestion);
    congestionTimer.setInterval(500);

    totalReroutes = 0;
    lastLogTime = QDateTime::currentSecsSinceEpoch();
}

void TrafficSimulator::start() {
    timer.start();
    congestionTimer.start();
}

void TrafficSimulator::stop() {
    timer.stop();
    congestionTimer.stop();
}

void TrafficSimulator::reset() {
    vehicles.clear();
    vehicleIndex.clear();
    trafficLights.clear();
    lightQueues.clear();
    lightReleaseTimers.clear();
    edgeVehicleCount.clear();
    manualJams.clear(); // <-- NEW
    nextVehicleId = 1;
    totalReroutes = 0;
}

// --- NEW ---
void TrafficSimulator::addManualJam(qint64 from, qint64 to)
{
    if (graph->hasNode(from) && graph->hasNode(to)) {
        manualJams.insert(qMakePair(from, to));
        // Also jam the other direction for simplicity
        manualJams.insert(qMakePair(to, from));
        qDebug() << "Manual jam added for edge" << from << "<->" << to;
    }
}
// --- END NEW ---
void TrafficSimulator::removeManualJam(qint64 from, qint64 to)
{
    manualJams.remove(qMakePair(from, to));
    manualJams.remove(qMakePair(to, from));
    qDebug() << "Manual jam removed for edge" << from << "<->" << to;
}

void TrafficSimulator::addVehicle(qint64 source, qint64 destination, bool priority) {
    if (!graph || !graph->hasNode(source) || !graph->hasNode(destination))
        return;

    // --- Use aStar for adding new vehicles ---
    Graph::PathResult path = graph->aStar(source, destination);
    if (!path.found || path.path.size() < 2)
        return;

    Vehicle v;
    v.id = nextVehicleId++;
    v.path = path.path;
    v.currentIndex = 0;
    v.progress = 0.0;
    v.baseSpeed = 10.0 + QRandomGenerator::global()->bounded(5.0);
    v.speed = v.baseSpeed;
    v.waitingAtLight = false;
    v.isPriority = priority;
    v.rerouted = false;
    v.lastRerouteTime = 0.0;
    v.color = priority ? QColor(Qt::red)
                       : QColor::fromHsl(QRandomGenerator::global()->bounded(360), 255, 150);

    Graph::Node n = graph->getNode(v.path.first());
    v.position = QPointF(n.lon, n.lat);

    vehicles.append(v);
    vehicleIndex[v.id] = vehicles.size() - 1;
}

void TrafficSimulator::updateSimulation() {
    double deltaTime = timer.interval() / 1000.0 * simulationSpeed;

    updateTrafficLights(deltaTime);
    updateQueues(deltaTime);
    updateVehicles(deltaTime);

    // --- MODIFIED ---
    // Emit traffic light data including queue size
    QVector<TrafficLight> lightsVector;
    lightsVector.reserve(trafficLights.size());
    for (auto it = trafficLights.begin(); it != trafficLights.end(); ++it) {
        it.value().queueSize = lightQueues.value(it.key()).size(); // <-- Add queue size
        lightsVector.append(it.value());
    }
    emit trafficLightsUpdated(lightsVector);
    // --- END MODIFIED ---

    emit vehiclesUpdated(vehicles);
}

void TrafficSimulator::updateTrafficLights(double deltaTime) {
    // Only initialize traffic lights if none exist
    if (trafficLights.isEmpty() && graph && !graph->getNodes().isEmpty()) {

        const double MIN_DISTANCE_METERS = 0.2; // ~200 meters
        for (auto it = graph->getNodes().cbegin(); it != graph->getNodes().cend(); ++it) {
            const auto& node = it.value();
            auto edges = graph->getEdges(node.id);

            // True intersection: at least 3 edges
            if (edges.size() < 3) continue;

            // Compute angles to detect fake or tight intersections
            QVector<double> angles;
            for (const auto& e : edges) {
                Graph::Node nbr = graph->getNode(e.to);
                double angleRad = qAtan2(nbr.lat - node.lat, nbr.lon - node.lon);
                angles.append(qRadiansToDegrees(angleRad));
            }
            std::sort(angles.begin(), angles.end());

            double minDiff = 360.0;
            for (int i = 1; i < angles.size(); i++)
                minDiff = qMin(minDiff, angles[i] - angles[i - 1]);
            minDiff = qMin(minDiff, 360.0 - (angles.last() - angles.first()));
            if (minDiff < 40.0) continue;

            // Prevent lights too close to each other
            bool tooClose = false;
            for (qint64 existing : trafficLights.keys()) {
                Graph::Node other = graph->getNode(existing);
                double dist = graph->haversineDistance(node.lat, node.lon,
                                                       other.lat, other.lon);
                if (dist < MIN_DISTANCE_METERS) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) continue;

            // Create the traffic light
            TrafficLight t;
            t.nodeId = node.id;
            t.isGreen = QRandomGenerator::global()->bounded(2) == 0;
            t.timer = 0.0;
            t.cycleDuration = 6.0;
            t.queueSize = 0;

            trafficLights[node.id] = t;
            lightQueues[node.id] = QQueue<qint64>();
            lightReleaseTimers[node.id] = 0.0;
        }

        qDebug() << "Traffic lights initialized:" << trafficLights.size();
    }

    // --- Adaptive light cycles ---
    for (auto it = trafficLights.begin(); it != trafficLights.end(); ++it) {
        int queueSize = lightQueues.value(it.key()).size();
        double adaptiveFactor = qBound(0.8, 1.0 + queueSize * 0.1, 1.5);
        double effectiveCycle = it->cycleDuration * adaptiveFactor;

        it->timer += deltaTime;
        if (it->timer >= effectiveCycle) {
            it->isGreen = !it->isGreen;
            it->timer = 0.0;
        }
    }
}

void TrafficSimulator::updateQueues(double deltaTime) {
    const double RELEASE_INTERVAL = 0.3;
    for (auto it = trafficLights.begin(); it != trafficLights.end(); ++it) {
        qint64 nodeId = it.key();
        if (!it->isGreen || !lightQueues.contains(nodeId)) continue;

        QQueue<qint64>& queue = lightQueues[nodeId];
        if (queue.isEmpty()) continue;

        lightReleaseTimers[nodeId] += deltaTime;
        if (lightReleaseTimers[nodeId] >= RELEASE_INTERVAL) {
            int idxToRelease = -1;
            // Priority first
            for (int i = 0; i < queue.size(); ++i) {
                int vidx = vehicleIndex.value(queue.at(i), -1);
                if (vidx >= 0 && vehicles[vidx].isPriority) {
                    idxToRelease = i;
                    break;
                }
            }
            if (idxToRelease == -1) idxToRelease = 0;

            qint64 releasedId = queue.takeAt(idxToRelease);
            lightReleaseTimers[nodeId] = 0.0;

            int idx = vehicleIndex.value(releasedId, -1);
            if (idx >= 0)
                vehicles[idx].waitingAtLight = false;
        }
    }
}

void TrafficSimulator::updateVehicles(double deltaTime) {
    const double MIN_GAP = 0.00002;
    edgeVehicleCount.clear();
    QHash<QPair<qint64,qint64>, QList<qint64>> edgeVehicles; // faster QHash

    for (const Vehicle& v : vehicles) {
        if (v.currentIndex >= v.path.size() - 1) continue;
        auto edge = qMakePair(v.path[v.currentIndex], v.path[v.currentIndex + 1]);
        edgeVehicleCount[edge] = edgeVehicleCount.value(edge, 0) + 1;
        edgeVehicles[edge].append(v.id);
    }

    // Inject manual jams into the vehicle count
    for (const auto& edge : manualJams) {
        edgeVehicleCount[edge] = 100; // Force a "Red" status
    }

    for (int i = 0; i < vehicles.size(); ++i) {
        Vehicle& v = vehicles[i];
        if (v.currentIndex >= v.path.size() - 1) continue;

        qint64 from = v.path[v.currentIndex];
        qint64 to = v.path[v.currentIndex + 1];

        Graph::Node n1 = graph->getNode(from);
        Graph::Node n2 = graph->getNode(to);

        double edgeLength = graph->haversineDistance(n1.lat, n1.lon, n2.lat, n2.lon);

        v.speed = v.baseSpeed * (0.95 + 0.1 * QRandomGenerator::global()->generateDouble());
        if (v.isPriority) v.speed *= 1.2;
        v.speed = qBound(5.0, v.speed, 25.0);

        bool stopForLight = false;
        if (trafficLights.contains(to)) {
            TrafficLight& light = trafficLights[to];
            if (!light.isGreen) {
                double remaining = edgeLength * (1.0 - v.progress);
                if (remaining < 1.5) { // smoother stop
                    if (v.isPriority) {
                        int vehiclesOnEdge = edgeVehicleCount.value(qMakePair(from,to),0);
                        stopForLight = vehiclesOnEdge > 2;
                    } else stopForLight = true;

                    if (stopForLight && !lightQueues[to].contains(v.id))
                        lightQueues[to].enqueue(v.id);
                    v.waitingAtLight = stopForLight;
                }
            }
        }

        // too close to next vehicle
        bool tooClose = false;
        const QList<qint64>& listOnEdge = edgeVehicles.value(qMakePair(from,to));
        for (qint64 otherId : listOnEdge) {
            if (otherId == v.id) continue;
            int otherIdx = vehicleIndex.value(otherId, -1);
            if (otherIdx < 0) continue;
            const Vehicle& other = vehicles[otherIdx];
            if (other.currentIndex == v.currentIndex && other.progress > v.progress) {
                if ((other.progress - v.progress) < MIN_GAP) { tooClose = true; break; }
            }
        }
        if (stopForLight || tooClose || v.waitingAtLight) continue;

        if (edgeLength <= 0.0) continue;
        v.progress += (v.speed * deltaTime) / edgeLength;
        if (v.progress > 1.0) {
            v.progress = 0.0;
            v.currentIndex++;
            if (v.currentIndex >= v.path.size()-1) continue;
        }

        Graph::Node a = graph->getNode(v.path[v.currentIndex]);
        Graph::Node b = graph->getNode(v.path[v.currentIndex+1]);

        QPointF pa = a.pos.isNull() ? QPointF(a.lon, a.lat) : a.pos;
        QPointF pb = b.pos.isNull() ? QPointF(b.lon, b.lat) : b.pos;
        v.position = interpolatePosition(pa, pb, v.progress);

        vehicleIndex[v.id] = i;
    }
}

void TrafficSimulator::updateCongestion() {
    for (auto it = edgeVehicleCount.begin(); it != edgeVehicleCount.end(); ++it) {
        QPair<qint64,qint64> edge = it.key();
        int count = it.value();
        QString status = "Green";

        // --- NEW ---
        // Manually jammed edges are always Red
        if (manualJams.contains(edge)) {
            status = "Red";
            count = 100; // ensure red status
        }
        // --- END NEW ---

        emit edgeCongestionUpdated(edge.first, edge.second, status);

        if (status == "Red") {
            for (Vehicle& v : vehicles) {
                if (v.currentIndex < v.path.size()-1 &&
                    v.path[v.currentIndex] == edge.first &&
                    v.path[v.currentIndex+1] == edge.second) {

                    qint64 now = QDateTime::currentSecsSinceEpoch();
                    if (v.rerouted && (now - v.lastRerouteTime) < rerouteCooldown)
                        continue; // cooldown active

                    QString email = QString("owner%1@mailtrap.test").arg(v.id);
                    QString subject = QString("Traffic Alert: Congestion Ahead (Vehicle %1)").arg(v.id);
                    QString body = QString(
                                       "Dear Driver %1,\n\n"
                                       "A congestion has been detected ahead on your route between nodes %2 and %3.\n"
                                       "Please consider an alternate route.\n\n"
                                       "— Smart Traffic Control System"
                                       ).arg(v.id).arg(edge.first).arg(edge.second);

                    notifier.sendCongestionEmail(email, v.id, subject, body);

                    if (!v.rerouted || (now - v.lastRerouteTime) >= rerouteCooldown) {
                        handleRerouting(v, edge);
                        v.lastRerouteTime = now;
                        v.rerouted = true;
                        totalReroutes++;
                    }
                }
            }
        }
    }

    // Log congestion stats every 10s
    qint64 now = QDateTime::currentSecsSinceEpoch();
    if (now - lastLogTime >= 10) {
        qDebug() << "[Stats] Edges:" << edgeVehicleCount.size()
        << "Total vehicles:" << vehicles.size()
        << "Total reroutes:" << totalReroutes;
        lastLogTime = now;
    }
}

// --- CORRECTED FUNCTION ---
void TrafficSimulator::handleRerouting(Vehicle& v, const QPair<qint64,qint64>& congestedEdge)
{
    qint64 destination = v.path.last();

    // --- FIX: Create a set of ALL blocked edges ---
    // Start with the manually created jams
    QSet<QPair<qint64, qint64>> allBlockedEdges = manualJams;

    // Add the current dynamic congestion
    allBlockedEdges.insert(congestedEdge);
    allBlockedEdges.insert(qMakePair(congestedEdge.second, congestedEdge.first)); // Add reverse direction

    // Find new path, avoiding ALL blocked edges
    Graph::PathResult newPathResult = graph->aStar(v.path[v.currentIndex],
                                                   destination,
                                                   allBlockedEdges); // <-- Pass the correct set

    if (newPathResult.found && newPathResult.path.size() >= 2) {
        v.path = newPathResult.path;
        v.currentIndex = 0; // Reset path index
        v.progress = 0.0;
        v.rerouted = true; // Flag the vehicle as rerouted
        v.lastRerouteTime = QDateTime::currentSecsSinceEpoch(); // Use seconds for cooldown

        qDebug() << "Vehicle" << v.id << "rerouted successfully.";
    } else {
        qDebug() << "Vehicle" << v.id << "could not find a reroute path.";
    }
}
// --- END CORRECTED FUNCTION ---

QPointF TrafficSimulator::interpolatePosition(const QPointF& a, const QPointF& b, double t) {
    return QPointF(a.x() + (b.x() - a.x()) * t, a.y() + (b.y() - a.y()) * t);
}
