#ifndef GRAPH_H
#define GRAPH_H

#include <QtGlobal>
#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QPointF>
#include <QVector>
#include <QByteArray> // Needed for JSON data
#include <QSet>

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
        QString name;
        QString streetName;
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
        QString displayName;
        double lat;
        double lon;
    };

    // Map parsing
    bool loadFromOSM(const QString& filePath); // Original function
    bool loadFromOverpassJSON(const QByteArray& jsonData); // New API parser

    // Graph queries
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const;
    bool hasNode(qint64 id) const { return nodes.contains(id); }

    // --- THIS IS THE IMPORTANT LINE ---
    Node getNode(qint64 id) const; // Takes ID by value, returns a copy

    const QMap<qint64, Node>& getNodes() const { return nodes; }
    QList<Edge> getEdges(qint64 nodeId) const { return adj.value(nodeId); }
    QList<qint64> getAllNodeIds() const { return nodes.keys(); }

    // Location name queries
    QList<NamedLocation> getNamedLocations() const;
    qint64 findNodeByName(const QString& name) const;
    QString getNodeDisplayName(qint64 nodeId) const;

    // Pathfinding
    PathResult dijkstra(qint64 source, qint64 destination); // Original
    PathResult aStar(qint64 source, qint64 destination, const QSet<QPair<qint64, qint64>>& blockedEdges = {});    // New

    // Clear graph
    void clear();

public:
    QMap<qint64, Node> nodes;
    QMap<qint64, QList<Edge>> adj;
    QMap<QString, qint64> nameToNodeId;

    // Helper functions
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    void addEdge(qint64 from, qint64 to, double distance);
    QString generateNodeName(const Node& node, int index) const;
    void generateDisplayNames();
};

#endif // GRAPH_H
