#include "graph.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>
#include <QSet>
#include <QPair>
#include <limits>
#include <algorithm>

Graph::Graph()
{
}

void Graph::clear()
{
    nodes.clear();
    adj.clear();
    nameToNodeId.clear();
}

bool Graph::loadFromOSM(const QString& filePath)
{
    clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QXmlStreamReader xml(&file);

    // First pass: Read all nodes and their tags
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == QString("node")) {
            Node node;
            node.id = xml.attributes().value("id").toLongLong();
            node.lat = xml.attributes().value("lat").toDouble();
            node.lon = xml.attributes().value("lon").toDouble();
            node.pos = QPointF(node.lon, node.lat);

            // Read all tags for this node
            while (!(xml.isEndElement() && xml.name() == QString("node"))) {
                xml.readNext();

                if (xml.isStartElement() && xml.name() == QString("tag")) {
                    QString key = xml.attributes().value("k").toString();
                    QString value = xml.attributes().value("v").toString();

                    // Priority order for node names
                    if (key == "name" && node.name.isEmpty()) {
                        node.name = value;
                    } else if (key == "name:en" && node.name.isEmpty()) {
                        node.name = value;
                    } else if (key == "addr:street" && node.streetName.isEmpty()) {
                        node.streetName = value;
                    } else if (key == "addr:suburb" && node.name.isEmpty()) {
                        node.name = value;
                    } else if (key == "addr:district" && node.name.isEmpty()) {
                        node.name = value;
                    } else if (key == "place" && node.name.isEmpty()) {
                        node.name = value + " Area";
                    } else if (key == "amenity" && node.name.isEmpty()) {
                        node.name = value.replace("_", " ");
                    } else if (key == "shop" && node.name.isEmpty()) {
                        node.name = value.replace("_", " ") + " Shop";
                    }
                }
            }

            nodes[node.id] = node;
        }
    }

    // Second pass: Read ways and build edges, extract street names
    file.seek(0);
    xml.setDevice(&file);

    QMap<qint64, QString> wayToStreetName;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == QString("way")) {
            qint64 wayId = xml.attributes().value("id").toLongLong();
            QList<qint64> wayNodes;
            QString wayName;
            QString roadType;
            bool isRoad = false;

            while (!(xml.isEndElement() && xml.name() == QString("way"))) {
                xml.readNext();

                if (xml.isStartElement() && xml.name() == QString("nd")) {
                    qint64 nodeRef = xml.attributes().value("ref").toLongLong();
                    wayNodes.append(nodeRef);
                }

                if (xml.isStartElement() && xml.name() == QString("tag")) {
                    QString key = xml.attributes().value("k").toString();
                    QString value = xml.attributes().value("v").toString();

                    // Check if this way is a road
                    if (key == "highway") {
                        isRoad = true;
                        roadType = value;
                    }

                    // Extract road/street name
                    if (key == "name") {
                        wayName = value;
                    } else if (key == "name:en" && wayName.isEmpty()) {
                        wayName = value;
                    } else if (key == "addr:street" && wayName.isEmpty()) {
                        wayName = value;
                    }
                }
            }

            // Only process if it's actually a road
            if (isRoad && !wayNodes.isEmpty()) {
                // Assign street name to nodes that don't have one
                if (!wayName.isEmpty()) {
                    for (qint64 nodeId : wayNodes) {
                        if (nodes.contains(nodeId)) {
                            if (nodes[nodeId].streetName.isEmpty()) {
                                nodes[nodeId].streetName = wayName;
                            }
                            // If node has no name at all, use street name
                            if (nodes[nodeId].name.isEmpty()) {
                                nodes[nodeId].name = wayName;
                            }
                        }
                    }
                }

                // Create edges between consecutive nodes
                for (int i = 0; i < wayNodes.size() - 1; ++i) {
                    qint64 from = wayNodes[i];
                    qint64 to = wayNodes[i + 1];

                    if (nodes.contains(from) && nodes.contains(to)) {
                        Node n1 = nodes[from];
                        Node n2 = nodes[to];

                        double dist = haversineDistance(n1.lat, n1.lon, n2.lat, n2.lon);

                        // Add bidirectional edges
                        addEdge(from, to, dist);
                        addEdge(to, from, dist);
                    }
                }
            }
        }
    }

    file.close();

    if (xml.hasError()) {
        return false;
    }

    // Generate smart display names for all nodes
    generateDisplayNames();

    return true;
}

void Graph::generateDisplayNames()
{
    nameToNodeId.clear();

    // Group nodes by their base names to add distinguishing info
    QMap<QString, QList<qint64>> nameGroups;

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Node& node = it.value();
        QString baseName;

        // Determine base name
        if (!node.name.isEmpty()) {
            baseName = node.name;
        } else if (!node.streetName.isEmpty()) {
            baseName = node.streetName;
        } else {
            baseName = "Unnamed Location";
        }

        nameGroups[baseName].append(node.id);
    }

    // Create unique display names
    int unnamedCounter = 1;
    for (auto it = nameGroups.begin(); it != nameGroups.end(); ++it) {
        QString baseName = it.key();
        QList<qint64> nodeIds = it.value();

        if (nodeIds.size() == 1) {
            // Unique name - just add coordinates
            qint64 nodeId = nodeIds.first();
            Node node = nodes[nodeId];
            QString displayName = QString("%1 (%2, %3)")
                                      .arg(baseName)
                                      .arg(node.lat, 0, 'f', 4)
                                      .arg(node.lon, 0, 'f', 4);
            nameToNodeId[displayName] = nodeId;
        } else {
            // Multiple nodes with same name - add more context
            for (int i = 0; i < nodeIds.size(); ++i) {
                qint64 nodeId = nodeIds[i];
                Node node = nodes[nodeId];

                QString displayName;
                if (baseName == "Unnamed Location") {
                    displayName = QString("Intersection #%1 (%2, %3)")
                    .arg(unnamedCounter++)
                        .arg(node.lat, 0, 'f', 4)
                        .arg(node.lon, 0, 'f', 4);
                } else {
                    // Add junction/intersection designation
                    displayName = QString("%1 - Junction %2 (%3, %4)")
                                      .arg(baseName)
                                      .arg(i + 1)
                                      .arg(node.lat, 0, 'f', 4)
                                      .arg(node.lon, 0, 'f', 4);
                }

                nameToNodeId[displayName] = nodeId;
            }
        }
    }
}

QString Graph::generateNodeName(const Node& node, int index) const
{
    QString name;

    if (!node.name.isEmpty()) {
        name = node.name;
    } else if (!node.streetName.isEmpty()) {
        name = node.streetName;
    } else {
        name = QString("Intersection #%1").arg(index);
    }

    name += QString(" (%1, %2)")
                .arg(node.lat, 0, 'f', 4)
                .arg(node.lon, 0, 'f', 4);

    return name;
}

QList<Graph::NamedLocation> Graph::getNamedLocations() const
{
    QList<NamedLocation> locations;

    for (auto it = nameToNodeId.constBegin(); it != nameToNodeId.constEnd(); ++it) {
        NamedLocation loc;
        loc.displayName = it.key();
        loc.nodeId = it.value();
        Node node = nodes[loc.nodeId];
        loc.lat = node.lat;
        loc.lon = node.lon;
        locations.append(loc);
    }

    // Sort alphabetically for easier browsing
    std::sort(locations.begin(), locations.end(),
              [](const NamedLocation& a, const NamedLocation& b) {
                  return a.displayName < b.displayName;
              });

    return locations;
}

qint64 Graph::findNodeByName(const QString& name) const
{
    return nameToNodeId.value(name, -1);
}

QString Graph::getNodeDisplayName(qint64 nodeId) const
{
    if (!nodes.contains(nodeId)) {
        return QString("Unknown Node");
    }

    // Find the display name for this node ID
    for (auto it = nameToNodeId.constBegin(); it != nameToNodeId.constEnd(); ++it) {
        if (it.value() == nodeId) {
            return it.key();
        }
    }

    // Fallback
    Node node = nodes[nodeId];
    return QString("Node %1 (%2, %3)")
        .arg(nodeId)
        .arg(node.lat, 0, 'f', 4)
        .arg(node.lon, 0, 'f', 4);
}

double Graph::haversineDistance(double lat1, double lon1, double lat2, double lon2)
{
    const double R = 6371.0;
    double dLat = qDegreesToRadians(lat2 - lat1);
    double dLon = qDegreesToRadians(lon2 - lon1);
    double rLat1 = qDegreesToRadians(lat1);
    double rLat2 = qDegreesToRadians(lat2);

    double a = qSin(dLat / 2.0) * qSin(dLat / 2.0) +
               qCos(rLat1) * qCos(rLat2) *
                   qSin(dLon / 2.0) * qSin(dLon / 2.0);

    double c = 2.0 * qAtan2(qSqrt(a), qSqrt(1.0 - a));
    double distance = R * c;

    return distance;
}

void Graph::addEdge(qint64 from, qint64 to, double distance)
{
    Edge edge;
    edge.to = to;
    edge.distance = distance;

    adj[from].append(edge);
}

int Graph::getEdgeCount() const
{
    int count = 0;
    for (const auto& edgeList : adj) {
        count += edgeList.size();
    }
    return count / 2;
}

Graph::PathResult Graph::dijkstra(qint64 source, qint64 destination)
{
    PathResult result;
    result.found = false;
    result.totalDistance = 0.0;

    if (!hasNode(source)) {
        result.errorMessage = "Source node not found in graph";
        return result;
    }
    if (!hasNode(destination)) {
        result.errorMessage = "Destination node not found in graph";
        return result;
    }
    if (source == destination) {
        result.found = true;
        result.path.append(source);
        result.totalDistance = 0.0;
        return result;
    }

    const double INF = std::numeric_limits<double>::infinity();
    QMap<qint64, double> dist;
    QMap<qint64, qint64> prev;
    QSet<qint64> visited;

    for (qint64 nodeId : nodes.keys()) {
        dist[nodeId] = INF;
    }
    dist[source] = 0.0;

    while (true) {
        qint64 current = -1;
        double minDist = INF;

        for (qint64 nodeId : nodes.keys()) {
            if (!visited.contains(nodeId) && dist[nodeId] < minDist) {
                minDist = dist[nodeId];
                current = nodeId;
            }
        }

        if (current == -1 || minDist == INF) {
            break;
        }

        if (current == destination) {
            break;
        }

        visited.insert(current);

        for (const Edge& edge : adj[current]) {
            if (!visited.contains(edge.to)) {
                double newDist = dist[current] + edge.distance;
                if (newDist < dist[edge.to]) {
                    dist[edge.to] = newDist;
                    prev[edge.to] = current;
                }
            }
        }
    }

    if (dist[destination] == INF) {
        result.errorMessage = "No path found between source and destination";
        return result;
    }

    QVector<qint64> path;
    qint64 current = destination;
    while (current != source) {
        path.prepend(current);
        if (!prev.contains(current)) {
            result.errorMessage = "Path reconstruction failed";
            return result;
        }
        current = prev[current];
    }
    path.prepend(source);

    result.found = true;
    result.path = path;
    result.totalDistance = dist[destination];

    return result;
}
