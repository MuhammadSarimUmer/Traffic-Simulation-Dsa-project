#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QPointF>
#include <QQueue>
#include <QHash>
#include <QMap>
#include <QPair>
#include <QSet> // <-- Added for manualJams
#include "graph.h"
#include "notification_manager.h"

class TrafficSimulator : public QObject
{
    Q_OBJECT

public:
    explicit TrafficSimulator(Graph* g, QObject* parent = nullptr);

    void start();
    void stop();
    void reset();
    void addVehicle(qint64 source, qint64 destination, bool priority = false);

    // --- NEW ---
    // Methods for live stats and manual jams
    void setSimulationSpeed(double speed) { simulationSpeed = speed; }
    int getVehicleCount() const { return vehicles.size(); }
    int getTrafficLightCount() const { return trafficLights.size(); }
    void addManualJam(qint64 from, qint64 to);
    // --- END NEW ---

    struct Vehicle {
        qint64 id;
        QVector<qint64> path;
        int currentIndex;
        double progress;
        double baseSpeed;
        double speed;
        bool waitingAtLight;
        bool isPriority;
        bool rerouted;
        QColor color;
        QPointF position;

        // Enhancements:
        qint64 lastRerouteTime;  // timestamp for reroute cooldown tracking

        bool canReroute(qint64 now, double cooldown) const {
            return (!rerouted || (now - lastRerouteTime) >= cooldown);
        }
    };

    struct TrafficLight {
        qint64 nodeId;
        bool isGreen;
        double timer;
        double cycleDuration;
        int queueSize; // <-- NEW: To show light only when active
    };

signals:
    void vehiclesUpdated(const QVector<Vehicle>& vehicles);
    void trafficLightsUpdated(const QVector<TrafficLight>& lights);
    void edgeCongestionUpdated(qint64 from, qint64 to, const QString& status);
    void congestionAlert(const QString& message);

private slots:
    void updateSimulation();
    void updateCongestion();

private:
    // Core update logic
    void updateTrafficLights(double deltaTime);
    void updateQueues(double deltaTime);
    void updateVehicles(double deltaTime);
    void handleRerouting(Vehicle& v, const QPair<qint64,qint64>& congestedEdge);
    QPointF interpolatePosition(const QPointF& a, const QPointF& b, double t);

    // --- Simulation Core ---
    Graph* graph;
    QTimer timer;
    QTimer congestionTimer;
    NotificationManager notifier;

    double simulationSpeed;
    qint64 nextVehicleId;

    QVector<Vehicle> vehicles;
    QHash<qint64, int> vehicleIndex;

    // switched to QHash for better performance on large graphs
    QHash<QPair<qint64,qint64>, int> edgeVehicleCount;
    QHash<qint64, TrafficLight> trafficLights;
    QHash<qint64, QQueue<qint64>> lightQueues;
    QHash<qint64, double> lightReleaseTimers;

    // --- Enhancements ---
    double rerouteCooldown;   // seconds before vehicle can reroute again
    qint64 totalReroutes;     // counter for monitoring
    qint64 lastLogTime;       // for periodic console stats
    QSet<QPair<qint64, qint64>> manualJams; // <-- NEW
};

#endif // TRAFFIC_SIMULATOR_H
