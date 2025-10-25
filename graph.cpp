#include "graph.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>

Graph::Graph()
{
}

void Graph::clear()
{
    nodes.clear();
    adj.clear();
}

bool Graph::loadFromOSM(const QString& filePath)
{
    clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QXmlStreamReader xml(&file);

    // First pass: Read all nodes
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == QString("node")) {
            Node node;
            node.id = xml.attributes().value("id").toLongLong();
            node.lat = xml.attributes().value("lat").toDouble();
            node.lon = xml.attributes().value("lon").toDouble();
            node.pos = QPointF(node.lon, node.lat); // For future rendering

            nodes[node.id] = node;
        }
    }

    // Reset to beginning for second pass
    file.seek(0);
    xml.setDevice(&file);

    // Second pass: Read all ways and build edges
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement() && xml.name() == QString("way")) {
            QList<qint64> wayNodes;

            // Read all node references in this way
            while (!(xml.isEndElement() && xml.name() == QString("way"))) {
                xml.readNext();

                if (xml.isStartElement() && xml.name() == QString("nd")) {
                    qint64 nodeRef = xml.attributes().value("ref").toLongLong();
                    wayNodes.append(nodeRef);
                }
            }

            // Create edges between consecutive nodes in the way
            for (int i = 0; i < wayNodes.size() - 1; ++i) {
                qint64 from = wayNodes[i];
                qint64 to = wayNodes[i + 1];

                // Only create edge if both nodes exist
                if (nodes.contains(from) && nodes.contains(to)) {
                    Node n1 = nodes[from];
                    Node n2 = nodes[to];

                    double dist = haversineDistance(n1.lat, n1.lon, n2.lat, n2.lon);

                    // Add bidirectional edges (assuming roads are two-way)
                    addEdge(from, to, dist);
                    addEdge(to, from, dist);
                }
            }
        }
    }

    file.close();

    if (xml.hasError()) {
        return false;
    }

    return true;
}

double Graph::haversineDistance(double lat1, double lon1, double lat2, double lon2)
{
    // Convert degrees to radians
    const double R = 6371.0; // Earth's radius in kilometers
    double dLat = qDegreesToRadians(lat2 - lat1);
    double dLon = qDegreesToRadians(lon2 - lon1);
    double rLat1 = qDegreesToRadians(lat1);
    double rLat2 = qDegreesToRadians(lat2);

    // Haversine formula
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
    // Divide by 2 since we count bidirectional edges twice
    return count / 2;
}
