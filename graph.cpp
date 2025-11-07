#include "graph.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>
#include <QSet>
#include <QPair>
#include <limits>
#include <algorithm>
#include <QQueue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <queue> // For std::priority_queue

Graph::Graph()
{
}

void Graph::clear()
{
    nodes.clear();
    adj.clear();
    nameToNodeId.clear();
}

// --- New API JSON Parser ---
bool Graph::loadFromOverpassJSON(const QByteArray &jsonData)
{
    clear();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qDebug() << "Failed to parse JSON: Not an object";
        return false;
    }

    QJsonObject root = doc.object();
    if (!root.contains("elements") || !root["elements"].isArray()) {
        qDebug() << "Failed to parse JSON: No 'elements' array found";
        return false;
    }

    QJsonArray elements = root["elements"].toArray();

    // First pass: Read all nodes
    for (const QJsonValue &val : elements) {
        QJsonObject obj = val.toObject();
        if (obj["type"].toString() == "node") {
            Node node;
            node.id = obj["id"].toVariant().toLongLong();
            node.lat = obj["lat"].toDouble();
            node.lon = obj["lon"].toDouble();
            node.pos = QPointF(node.lon, node.lat);

            // Read tags for this node
            if (obj.contains("tags") && obj["tags"].isObject()) {
                QJsonObject tags = obj["tags"].toObject();
                // Priority order for node names
                if (tags.contains("name")) node.name = tags["name"].toString();
                if (tags.contains("name:en") && node.name.isEmpty()) node.name = tags["name:en"].toString();
                if (tags.contains("addr:street")) node.streetName = tags["addr:street"].toString();
                if (tags.contains("addr:suburb") && node.name.isEmpty()) node.name = tags["addr:suburb"].toString();
            }

            nodes[node.id] = node;
        }
    }

    qDebug() << "Loaded" << nodes.size() << "nodes from API.";

    // Second pass: Read ways and build edges
    for (const QJsonValue &val : elements) {
        QJsonObject obj = val.toObject();
        if (obj["type"].toString() == "way") {
            // Check if this way is a road (must have "highway" tag)
            if (!obj.contains("tags") || !obj["tags"].isObject() ||
                !obj["tags"].toObject().contains("highway")) {
                continue;
            }

            QJsonObject tags = obj["tags"].toObject();
            QString wayName;
            if (tags.contains("name")) wayName = tags["name"].toString();
            if (tags.contains("name:en") && wayName.isEmpty()) wayName = tags["name:en"].toString();
            if (tags.contains("addr:street") && wayName.isEmpty()) wayName = tags["addr:street"].toString();

            QJsonArray wayNodes = obj["nodes"].toArray();
            if (wayNodes.size() < 2) continue;

            for (int i = 0; i < wayNodes.size(); ++i) {
                qint64 nodeId = wayNodes[i].toVariant().toLongLong();
                if (nodes.contains(nodeId)) {
                    // Assign street name to nodes that don't have one
                    if (!wayName.isEmpty()) {
                        if (nodes[nodeId].streetName.isEmpty()) {
                            nodes[nodeId].streetName = wayName;
                        }
                        if (nodes[nodeId].name.isEmpty()) {
                            nodes[nodeId].name = wayName;
                        }
                    }
                }
            }

            // Create edges between consecutive nodes
            for (int i = 0; i < wayNodes.size() - 1; ++i) {
                qint64 from = wayNodes[i].toVariant().toLongLong();
                qint64 to = wayNodes[i + 1].toVariant().toLongLong();

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

    qDebug() << "Built edges. Total edges (one-way):" << getEdgeCount();

    // Generate smart display names for all nodes
    generateDisplayNames();
    qDebug() << "Generated display names. Named locations:" << nameToNodeId.size();

    return true;
}


// --- Original OSM File Loader (From your file) ---
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

// --- getNode Definition ---
Graph::Node Graph::getNode(qint64 id) const
{
    return nodes.value(id);
}


// --- generateDisplayNames and other helpers ---
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
    return count / 2; // Divided by 2 because we add bidirectional edges
}

// --- Original Dijkstra Implementation ---
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


// --- Fixed A* Implementation ---
Graph::PathResult Graph::aStar(qint64 source, qint64 destination)
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

    // Use std::priority_queue with custom comparator for min-heap
    // Format: pair<priority, nodeId>
    using PriorityNode = QPair<double, qint64>;

    // Custom comparator: greater priority value = lower priority in queue (min-heap)
    auto compare = [](const PriorityNode& a, const PriorityNode& b) {
        return a.first > b.first; // Min-heap: smallest priority first
    };

    std::priority_queue<PriorityNode, std::vector<PriorityNode>, decltype(compare)> pq(compare);

    QMap<qint64, double> costSoFar; // g_score: cost from source
    QMap<qint64, qint64> cameFrom;  // For path reconstruction
    QSet<qint64> visited; // Track processed nodes

    Node destNode = getNode(destination);

    // Initialize all costs to infinity
    for (qint64 nodeId : nodes.keys()) {
        costSoFar[nodeId] = INF;
    }

    // Start with source node
    costSoFar[source] = 0.0;
    Node sourceNode = getNode(source);
    double heuristic = haversineDistance(sourceNode.lat, sourceNode.lon,
                                         destNode.lat, destNode.lon);

    pq.push({heuristic, source}); // Priority = f_score = g + h = 0 + h

    while (!pq.empty()) {
        qint64 current = pq.top().second;
        pq.pop();

        // Skip if already processed
        if (visited.contains(current)) {
            continue;
        }
        visited.insert(current);

        // Found destination
        if (current == destination) {
            break;
        }

        // Explore neighbors
        for (const Edge& edge : adj[current]) {
            if (visited.contains(edge.to)) {
                continue; // Already processed
            }

            double newCost = costSoFar[current] + edge.distance;

            // If this path is better, update it
            if (newCost < costSoFar[edge.to]) {
                costSoFar[edge.to] = newCost;
                cameFrom[edge.to] = current;

                // Calculate f_score = g + h
                Node neighborNode = getNode(edge.to);
                double h = haversineDistance(neighborNode.lat, neighborNode.lon,
                                             destNode.lat, destNode.lon);
                double fScore = newCost + h;

                pq.push({fScore, edge.to});
            }
        }
    }

    // Check if path was found
    if (costSoFar[destination] == INF) {
        result.errorMessage = "No path found between source and destination";
        return result;
    }

    // Reconstruct path
    QVector<qint64> path;
    qint64 current = destination;
    while (current != source) {
        path.prepend(current);
        if (!cameFrom.contains(current)) {
            result.errorMessage = "Path reconstruction failed";
            return result;
        }
        current = cameFrom[current];
    }
    path.prepend(source);

    result.found = true;
    result.path = path;
    result.totalDistance = costSoFar[destination];

    return result;
}
