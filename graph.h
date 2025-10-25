#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QPointF>

class Graph
{
public:
    Graph();

    // Core data structures
    struct Node {
        qint64 id;
        double lat;
        double lon;
        QPointF pos; // For future GUI rendering
    };

    struct Edge {
        qint64 to;
        double distance; // in kilometers
    };

    // Map parsing
    bool loadFromOSM(const QString& filePath);

    // Graph queries
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const;
    bool hasNode(qint64 id) const { return nodes.contains(id); }
    Node getNode(qint64 id) const { return nodes.value(id); }
    QList<Edge> getEdges(qint64 nodeId) const { return adj.value(nodeId); }

    // Clear graph
    void clear();

private:
    QMap<qint64, Node> nodes;           // node_id -> Node data
    QMap<qint64, QList<Edge>> adj;      // adjacency list

    // Helper functions
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    void addEdge(qint64 from, qint64 to, double distance);
};

#endif // GRAPH_H
