#include "traffic_simulator.h"
#include <QtMath>
#include <QDebug>
#include <QQueue>

TrafficSimulator::TrafficSimulator(Graph* g, QObject* parent)
    : QObject(parent),
    graph(g),
    simulationSpeed(1.0),
    nextVehicleId(1)
{
    connect(&timer, &QTimer::timeout, this, &TrafficSimulator::updateSimulation);
    timer.setInterval(50); // 20 updates/sec (~smooth)
}

void TrafficSimulator::start() { timer.start(); }
void TrafficSimulator::stop() { timer.stop(); }

void TrafficSimulator::reset() {
    vehicles.clear();
    trafficLights.clear();
    lightQueues.clear();
    lightReleaseTimers.clear();  // ✅ Added to track queue release timing
    nextVehicleId = 1;
}

void TrafficSimulator::addVehicle(qint64 source, qint64 destination)
{
    if (!graph->hasNode(source) || !graph->hasNode(destination))
        return;

    Graph::PathResult path = graph->dijkstra(source, destination);
    if (!path.found || path.path.size() < 2)
        return;

    Vehicle v;
    v.id = nextVehicleId++;
    v.path = path.path;
    v.currentIndex = 0;
    v.progress = 0.0;
    v.speed = 10.0 + QRandomGenerator::global()->bounded(5.0);
    v.waitingAtLight = false;
    v.color = QColor::fromHsl(QRandomGenerator::global()->bounded(360), 255, 150);

    const Graph::Node& n = graph->getNode(v.path.first());
    v.position = QPointF(n.lon, n.lat);

    vehicles.append(v);
}

void TrafficSimulator::updateSimulation()
{
    double deltaTime = timer.interval() / 1000.0 * simulationSpeed;

    updateTrafficLights(deltaTime);
    updateQueues(deltaTime);     // 🚦 New: handle queue release timing
    updateVehicles(deltaTime);

    emit vehiclesUpdated(vehicles);
    emit trafficLightsUpdated(trafficLights.values().toVector());
}

void TrafficSimulator::updateTrafficLights(double deltaTime)
{
    if (trafficLights.isEmpty() && !graph->getNodes().isEmpty()) {
        int count = 0;
        for (auto it = graph->getNodes().cbegin(); it != graph->getNodes().cend(); ++it) {
            if (count % 20 == 0) {
                TrafficLight t;
                t.nodeId = it.key();
                t.isGreen = (count % 40 == 0);
                t.timer = 0.0;
                t.cycleDuration = 10.0;
                trafficLights[t.nodeId] = t;

                // 🚦 create queue and timer for this light
                lightQueues[t.nodeId] = QQueue<qint64>();
                lightReleaseTimers[t.nodeId] = 0.0;
            }
            count++;
        }
    }

    // Cycle lights
    for (auto it = trafficLights.begin(); it != trafficLights.end(); ++it) {
        it->timer += deltaTime;
        if (it->timer >= it->cycleDuration) {
            it->isGreen = !it->isGreen;
            it->timer = 0.0;

            if (it->isGreen)
                qDebug() << "Light GREEN at node" << it.key() << "- vehicles will start releasing";
        }
    }
}

// 🚦 New: gradual vehicle release logic
void TrafficSimulator::updateQueues(double deltaTime)
{
    const double RELEASE_INTERVAL = 1.0; // release one vehicle per second

    for (auto it = trafficLights.begin(); it != trafficLights.end(); ++it) {
        qint64 nodeId = it.key();

        if (!it->isGreen)
            continue; // only release when green

        if (!lightQueues.contains(nodeId))
            continue;

        QQueue<qint64>& queue = lightQueues[nodeId];
        if (queue.isEmpty())
            continue;

        // increment timer
        lightReleaseTimers[nodeId] += deltaTime;

        // if enough time passed, release next car
        if (lightReleaseTimers[nodeId] >= RELEASE_INTERVAL) {
            int releasedId = queue.dequeue();
            lightReleaseTimers[nodeId] = 0.0;

            for (Vehicle &v : vehicles) {
                if (v.id == releasedId) {
                    v.waitingAtLight = false;
                    qDebug() << "Vehicle" << v.id << "released from queue at light" << nodeId
                             << "remaining queue size:" << queue.size();
                    break;
                }
            }
        }
    }
}

void TrafficSimulator::updateVehicles(double deltaTime)
{
    const double MIN_GAP = 0.0002;

    for (int i = 0; i < vehicles.size(); ++i) {
        Vehicle &v = vehicles[i];

        if (v.currentIndex >= v.path.size() - 1)
            continue;

        qint64 from = v.path[v.currentIndex];
        qint64 to = v.path[v.currentIndex + 1];

        const Graph::Node &n1 = graph->getNode(from);
        const Graph::Node &n2 = graph->getNode(to);
        double edgeLength = graph->haversineDistance(n1.lat, n1.lon, n2.lat, n2.lon);

        // Traffic light + queue logic
        bool stopForLight = false;
        if (trafficLights.contains(to)) {
            TrafficLight &light = trafficLights[to];
            if (!light.isGreen) {
                double remaining = edgeLength * (1.0 - v.progress);
                if (remaining < 0.001) {
                    stopForLight = true;
                    v.waitingAtLight = true;

                    // enqueue if not already queued
                    if (!lightQueues[to].contains(v.id)) {
                        lightQueues[to].enqueue(v.id);
                        qDebug() << "Vehicle" << v.id << "queued at red light" << to
                                 << "queue size:" << lightQueues[to].size();
                    }
                }
            }
        }

        // Collision check
        bool tooClose = false;
        for (int j = 0; j < vehicles.size(); ++j) {
            if (i == j) continue;
            Vehicle &other = vehicles[j];
            if (other.currentIndex == v.currentIndex && other.progress > v.progress) {
                double diff = other.progress - v.progress;
                if (diff < MIN_GAP)
                    tooClose = true;
            }
        }

        // Stop if red light, queued, or too close
        if (stopForLight || tooClose || v.waitingAtLight)
            continue;

        // Move vehicle
        v.progress += (v.speed * deltaTime) / (edgeLength * 1000.0);
        if (v.progress > 1.0) {
            v.progress = 0.0;
            v.currentIndex++;
            if (v.currentIndex >= v.path.size() - 1)
                continue;
        }

        // Update position
        const Graph::Node &a = graph->getNode(v.path[v.currentIndex]);
        const Graph::Node &b = graph->getNode(v.path[v.currentIndex + 1]);
        v.position = interpolatePosition(a.pos, b.pos, v.progress);
    }
}

QPointF TrafficSimulator::interpolatePosition(const QPointF& a, const QPointF& b, double t)
{
    return QPointF(a.x() + (b.x() - a.x()) * t,
                   a.y() + (b.y() - a.y()) * t);
}
