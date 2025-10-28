#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QQueue>
#include <QRandomGenerator>
#include <QColor>
#include "graph.h"

struct Vehicle {
    qint64 id;
    QVector<qint64> path;    // sequence of node IDs
    int currentIndex;         // current edge index in path
    double progress;          // 0.0 - 1.0 along edge
    double speed;             // m/s
    bool waitingAtLight;
    QColor color;
    QPointF position;         // screen/map position

    Vehicle()
        : id(0), currentIndex(0), progress(0.0), speed(0.0),
        waitingAtLight(false), position(0,0) {}
};

struct TrafficLight {
    qint64 nodeId;
    bool isGreen;
    double timer;
    double cycleDuration;     // seconds
};

class TrafficSimulator : public QObject
{
    Q_OBJECT
public:
    explicit TrafficSimulator(Graph* graph, QObject* parent = nullptr);

    void start();
    void stop();
    void addVehicle(qint64 source, qint64 destination);
    void reset();

signals:
    void vehiclesUpdated(const QVector<Vehicle>& vehicles);
    void trafficLightsUpdated(const QVector<TrafficLight>& lights);

private slots:
    void updateSimulation();

private:
    Graph* graph;
    QTimer timer;
    QVector<Vehicle> vehicles;
    QMap<qint64, TrafficLight> trafficLights;

    // Per-node queues and release timers (used from cpp)
    QMap<qint64, QQueue<qint64>> lightQueues;      // keyed by nodeId, stores vehicle ids
    QMap<qint64, double> lightReleaseTimers;       // keyed by nodeId

    double simulationSpeed;   // simulation time multiplier
    qint64 nextVehicleId;

    void updateQueues(double deltaTime);
    void updateVehicles(double deltaTime);
    void updateTrafficLights(double deltaTime);
    QPointF interpolatePosition(const QPointF& a, const QPointF& b, double t);
};

#endif // TRAFFIC_SIMULATOR_H
