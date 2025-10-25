#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QPointF>
#include <QVector>

class Graph
{
public:
    Graph();

    // Core data structures
    struct Node {
        qint64 id;
        double lat;
        double lon;
        QPointF pos;
        QString name;        // Location name (e.g., "Gulshan-e-Iqbal")
        QString streetName;  // Street name if available
    };

    struct Edge {
        qint64 to;
        double distance;
    };

    struct PathResult {
        bool found;
        QVector<qint64> path;
        double totalDistance;
        QString errorMessage;
    };

    struct NamedLocation {
        qint64 nodeId;
        QString displayName;  // "Gulshan-e-Iqbal (24.8600, 67.0100)"
        double lat;
        double lon;
    };

    // Map parsing
    bool loadFromOSM(const QString& filePath);

    // Graph queries
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const;
    bool hasNode(qint64 id) const { return nodes.contains(id); }
    Node getNode(qint64 id) const { return nodes.value(id); }
    QList<Edge> getEdges(qint64 nodeId) const { return adj.value(nodeId); }
    QList<qint64> getAllNodeIds() const { return nodes.keys(); }

    // Location name queries
    QList<NamedLocation> getNamedLocations() const;
    qint64 findNodeByName(const QString& name) const;
    QString getNodeDisplayName(qint64 nodeId) const;

    // Pathfinding
    PathResult dijkstra(qint64 source, qint64 destination);

    // Clear graph
    void clear();

private:
    QMap<qint64, Node> nodes;
    QMap<qint64, QList<Edge>> adj;
    QMap<QString, qint64> nameToNodeId;  // Location name → node ID

    // Helper functions
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    void addEdge(qint64 from, qint64 to, double distance);
    QString generateNodeName(const Node& node, int index) const;
    void generateDisplayNames();
};

#endif // GRAPH_H
