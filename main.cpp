#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "graph.h"
#include "traffic_simulator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // -----------------------------
    // 1️⃣ Load or create map
    // -----------------------------
    Graph graph;

    QString osmFile = "karachi.osm"; // optional OSM file path
    bool loaded = graph.loadFromOSM(osmFile);

    if (!loaded || graph.getNodeCount() == 0) {
        qWarning() << "Could not load OSM file — creating small test map.";

        // Create a few test nodes manually (Karachi coordinates)
        Graph::Node n1{1, 24.8607, 67.0011, QPointF(67.0011, 24.8607), "Start", "Road A"};
        Graph::Node n2{2, 24.8610, 67.0020, QPointF(67.0020, 24.8610), "Middle", "Road B"};
        Graph::Node n3{3, 24.8613, 67.0030, QPointF(67.0030, 24.8613), "End", "Road C"};

        graph.nodes[n1.id] = n1;
        graph.nodes[n2.id] = n2;
        graph.nodes[n3.id] = n3;

        double d1 = graph.haversineDistance(n1.lat, n1.lon, n2.lat, n2.lon);
        double d2 = graph.haversineDistance(n2.lat, n2.lon, n3.lat, n3.lon);

        graph.addEdge(n1.id, n2.id, d1);
        graph.addEdge(n2.id, n3.id, d2);

        qDebug() << "Created test graph with" << graph.getNodeCount() << "nodes.";
    } else {
        qDebug() << "Loaded OSM graph with" << graph.getNodeCount() << "nodes.";
    }

    // -----------------------------
    // 2️⃣ Create Traffic Simulator
    // -----------------------------
    TrafficSimulator simulator(&graph);
    simulator.start();

    // -----------------------------
    // 3️⃣ Connect signals
    // -----------------------------
    QObject::connect(&simulator, &TrafficSimulator::vehiclesUpdated,
                     [](const QVector<Vehicle>& vehicles) {
                         for (const auto &v : vehicles) {
                             qDebug() << "🚗 Vehicle" << v.id
                                      << "pos:" << v.position
                                      << "progress:" << v.progress
                                      << (v.waitingAtLight ? "(waiting)" : "");
                         }
                     });

    QObject::connect(&simulator, &TrafficSimulator::trafficLightsUpdated,
                     [](const QVector<TrafficLight>& lights) {
                         for (const auto &l : lights) {
                             qDebug() << "🚦 Light at node" << l.nodeId
                                      << (l.isGreen ? "GREEN" : "RED");
                         }
                     });

    // -----------------------------
    // 4️⃣ Spawn vehicles periodically
    // -----------------------------
    QTimer spawner;
    QObject::connect(&spawner, &QTimer::timeout, [&]() {
        auto nodeIds = graph.getAllNodeIds();
        if (nodeIds.size() < 2) return;

        qint64 src = nodeIds[QRandomGenerator::global()->bounded(nodeIds.size())];
        qint64 dst = nodeIds[QRandomGenerator::global()->bounded(nodeIds.size())];
        if (src == dst) return;

        simulator.addVehicle(src, dst);
        qDebug() << "Added vehicle from" << src << "to" << dst;
    });
    spawner.start(5000); // spawn every 5 seconds

    // -----------------------------
    // 5️⃣ Run application loop
    // -----------------------------
    return app.exec();
}
