#include "mapwidget.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QPalette>
#include <QtMath>
#include <QNetworkRequest>
#include <QUrl>
#include <cmath>
#include <QTimer>

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(240, 240, 240));
    setPalette(pal);

    setMouseTracking(true);

    networkManager = new QNetworkAccessManager(this);
    networkManager->setAutoDeleteReplies(true);

    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MapWidget::onTileDownloaded);

    showHighlight = false;
}

void MapWidget::setGraphData(const Graph& graphData)
{
    clearHighlight();
    currentGraph = graphData;
    clearPath();
    calculateBounds();
    updateCenter();
    update();
}

void MapWidget::setShortestPath(const QList<qint64>& path)
{
    currentPath = path;
    update();
}

void MapWidget::clearPath()
{
    currentPath.clear();
    update();
}

void MapWidget::setVehicles(const QVector<TrafficSimulator::Vehicle>& vehicles)
{
    currentVehicles = vehicles;
    update();
}

void MapWidget::setTrafficLights(const QVector<TrafficSimulator::TrafficLight>& lights)
{
    currentTrafficLights = lights;
    update();
}

void MapWidget::clearTrafficVisualization()
{
    currentVehicles.clear();
    currentTrafficLights.clear();
    update();
}

void MapWidget::calculateBounds()
{
    if (currentGraph.getNodeCount() == 0) {
        minLat = minLon = maxLat = maxLon = 0.0;
        return;
    }

    const QList<Graph::NamedLocation> locations = currentGraph.getNamedLocations();
    if (locations.isEmpty()) return;

    const Graph::Node firstNode = currentGraph.getNode(locations.first().nodeId);

    minLat = maxLat = firstNode.lat;
    minLon = maxLon = firstNode.lon;

    for (const auto& loc : locations) {
        const Graph::Node node = currentGraph.getNode(loc.nodeId);

        if (node.lat < minLat) minLat = node.lat;
        if (node.lat > maxLat) maxLat = node.lat;
        if (node.lon < minLon) minLon = node.lon;
        if (node.lon > maxLon) maxLon = node.lon;
    }

    double latBuffer = (maxLat - minLat) * 0.1;
    double lonBuffer = (maxLon - minLon) * 0.1;
    minLat -= latBuffer; maxLat += latBuffer;
    minLon -= lonBuffer; maxLon += lonBuffer;
}

void MapWidget::updateCenter()
{
    centerLat = (minLat + maxLat) / 2.0;
    centerLon = (minLon + maxLon) / 2.0;
}

double MapWidget::lon2tilex(double lon, int z)
{
    return (lon + 180.0) / 360.0 * (1 << z);
}

double MapWidget::lat2tiley(double lat, int z)
{
    double latRad = qDegreesToRadians(lat);
    return (1.0 - std::log(std::tan(latRad) + 1.0 / std::cos(latRad)) / M_PI) / 2.0 * (1 << z);
}

double MapWidget::tilex2lon(int x, int z)
{
    return x / (double)(1 << z) * 360.0 - 180.0;
}

double MapWidget::tiley2lat(int y, int z)
{
    double n = M_PI - 2.0 * M_PI * y / (double)(1 << z);
    return qRadiansToDegrees(std::atan(std::sinh(n)));
}

QPointF MapWidget::latLonToTile(double lat, double lon, int zoom)
{
    double x = lon2tilex(lon, zoom);
    double y = lat2tiley(lat, zoom);
    return QPointF(x, y);
}

QPointF MapWidget::geoToPixel(double lat, double lon)
{
    QPointF tile = latLonToTile(lat, lon, zoomLevel);
    QPointF centerTile = latLonToTile(centerLat, centerLon, zoomLevel);

    double pixelX = (tile.x() - centerTile.x()) * TILE_SIZE + width() / 2.0;
    double pixelY = (tile.y() - centerTile.y()) * TILE_SIZE + height() / 2.0;

    return QPointF(pixelX, pixelY);
}

QString MapWidget::getTileKey(int x, int y, int z)
{
    return QString("%1_%2_%3").arg(z).arg(x).arg(y);
}

void MapWidget::downloadTile(int x, int y, int z)
{
    QString key = getTileKey(x, y, z);

    if (tileCache.contains(key) || pendingTiles.contains(key)) {
        return;
    }

    pendingTiles.insert(key);

    QStringList tileServers = {
        QString("https://tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://a.tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://b.tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://c.tile.openstreetmap.org/%1/%2/%3.png"),
    };

    static int serverIndex = 0;
    QString urlTemplate = tileServers[serverIndex % tileServers.size()];
    serverIndex++;

    QString url = urlTemplate.arg(z).arg(x).arg(y);

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "TrafficSimulatorKarachi/1.0 (Qt Application)");
    request.setRawHeader("Accept", "image/png,image/*;q=0.8,*/*;q=0.5");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.9");
    request.setRawHeader("Connection", "keep-alive");
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setAttribute(QNetworkRequest::CacheSaveControlAttribute, true);
    request.setTransferTimeout(5000);

    QNetworkReply *reply = networkManager->get(request);
    reply->setProperty("tileKey", key);
    reply->setProperty("tileX", x);
    reply->setProperty("tileY", y);
    reply->setProperty("tileZ", z);

    qDebug() << "Downloading tile:" << key << "from" << url;
}

void MapWidget::onTileDownloaded(QNetworkReply *reply)
{
    if (!reply) return;

    QString key = reply->property("tileKey").toString();
    pendingTiles.remove(key);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        if (data.isEmpty()) {
            qWarning() << "Empty tile data for:" << key;
            return;
        }

        QPixmap pixmap;
        if (pixmap.loadFromData(data)) {
            tileCache[key] = pixmap;
            qDebug() << "Tile loaded:" << key << "Size:" << data.size() << "bytes";
            update();
        } else {
            qWarning() << "Failed to create pixmap from tile data:" << key;
        }
    } else {
        qWarning() << "Tile download failed:" << reply->error() << reply->errorString() << "for" << key;

        if (!failedTiles.contains(key)) {
            failedTiles.insert(key);
            pendingTiles.remove(key);

            int x = reply->property("tileX").toInt();
            int y = reply->property("tileY").toInt();
            int z = reply->property("tileZ").toInt();

            qDebug() << "Retrying tile:" << key;
            QTimer::singleShot(1000, this, [this, x, y, z]() {
                downloadTile(x, y, z);
            });
        }
    }
}

void MapWidget::drawTiles(QPainter &painter)
{
    if (minLat == 0.0 && maxLat == 0.0) {
        painter.fillRect(rect(), QColor(240, 240, 240));
        painter.setPen(Qt::darkGray);
        QFont font = painter.font();
        font.setPointSize(12);
        painter.setFont(font);
        painter.drawText(rect(), Qt::AlignCenter,
                         "Select an area and click 'Load Map Area' to begin");
        return;
    }

    QPointF centerTile = latLonToTile(centerLat, centerLon, zoomLevel);
    int centerTileX = qFloor(centerTile.x());
    int centerTileY = qFloor(centerTile.y());
    int tilesX = qCeil(width() / (double)TILE_SIZE) + 2;
    int tilesY = qCeil(height() / (double)TILE_SIZE) + 2;

    for (int dx = -tilesX/2; dx <= tilesX/2; ++dx) {
        for (int dy = -tilesY/2; dy <= tilesY/2; ++dy) {
            int tileX = centerTileX + dx;
            int tileY = centerTileY + dy;

            int maxTile = (1 << zoomLevel) - 1;
            if (tileX < 0 || tileX > maxTile || tileY < 0 || tileY > maxTile) {
                continue;
            }

            QString key = getTileKey(tileX, tileY, zoomLevel);
            double pixelX = (tileX - centerTile.x()) * TILE_SIZE + width() / 2.0;
            double pixelY = (tileY - centerTile.y()) * TILE_SIZE + height() / 2.0;

            if (tileCache.contains(key)) {
                painter.drawPixmap(QPointF(pixelX, pixelY), tileCache[key]);
            } else {
                painter.fillRect(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE), QColor(229, 227, 223));
                painter.setPen(QPen(QColor(200, 200, 200), 1));
                painter.drawRect(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE));
                painter.setPen(QColor(170, 170, 170));
                QFont smallFont = painter.font();
                smallFont.setPointSize(9);
                painter.setFont(smallFont);
                painter.drawText(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE), Qt::AlignCenter, "⏳");

                if (pendingTiles.size() < 10) {
                    downloadTile(tileX, tileY, zoomLevel);
                }
            }
        }
    }
}

void MapWidget::drawGraph(QPainter &painter)
{
    return;
}

void MapWidget::drawLoadedAreaOverlay(QPainter &painter)
{
    if (!hasLoadedArea) return;

    QPointF topLeft = geoToPixel(loadedAreaBounds.maxLat, loadedAreaBounds.minLon);
    QPointF topRight = geoToPixel(loadedAreaBounds.maxLat, loadedAreaBounds.maxLon);
    QPointF bottomLeft = geoToPixel(loadedAreaBounds.minLat, loadedAreaBounds.minLon);
    QPointF bottomRight = geoToPixel(loadedAreaBounds.minLat, loadedAreaBounds.maxLon);

    QPolygonF poly;
    poly << topLeft << topRight << bottomRight << bottomLeft;

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(135, 206, 250, 180), 3, Qt::SolidLine));
    painter.setBrush(QColor(173, 216, 230, 40));
    painter.drawPolygon(poly);
}

void MapWidget::drawHighlight(QPainter &painter)
{
    if (!showHighlight) return;

    QPointF topLeft = geoToPixel(highlightArea.maxLat, highlightArea.minLon);
    QPointF topRight = geoToPixel(highlightArea.maxLat, highlightArea.maxLon);
    QPointF bottomLeft = geoToPixel(highlightArea.minLat, highlightArea.minLon);
    QPointF bottomRight = geoToPixel(highlightArea.minLat, highlightArea.maxLon);

    QPolygonF poly;
    poly << topLeft << topRight << bottomRight << bottomLeft;

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(66, 133, 244, 200), 2, Qt::DashLine));
    painter.setBrush(QColor(66, 133, 244, 50));
    painter.drawPolygon(poly);
}

void MapWidget::drawPath(QPainter &painter)
{
    if (currentPath.size() < 2) return;

    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw white border
    painter.setPen(QPen(Qt::white, 14, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < currentPath.size() - 1; ++i) {
        const Graph::Node fromNode = currentGraph.getNode(currentPath[i]);
        const Graph::Node toNode = currentGraph.getNode(currentPath[i + 1]);
        QPointF start = geoToPixel(fromNode.lat, fromNode.lon);
        QPointF end = geoToPixel(toNode.lat, toNode.lon);
        painter.drawLine(start, end);
    }

    // Draw blue line
    painter.setPen(QPen(QColor(66, 133, 244), 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < currentPath.size() - 1; ++i) {
        const Graph::Node fromNode = currentGraph.getNode(currentPath[i]);
        const Graph::Node toNode = currentGraph.getNode(currentPath[i + 1]);
        QPointF start = geoToPixel(fromNode.lat, fromNode.lon);
        QPointF end = geoToPixel(toNode.lat, toNode.lon);
        painter.drawLine(start, end);
    }

    // Draw markers
    const Graph::Node startNode = currentGraph.getNode(currentPath.first());
    QPointF startPos = geoToPixel(startNode.lat, startNode.lon);
    painter.setPen(QPen(Qt::white, 4));
    painter.setBrush(QColor(52, 168, 83));
    painter.drawEllipse(startPos, 14, 14);
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(QRectF(startPos.x() - 14, startPos.y() - 14, 28, 28), Qt::AlignCenter, "A");

    const Graph::Node endNode = currentGraph.getNode(currentPath.last());
    QPointF endPos = geoToPixel(endNode.lat, endNode.lon);
    painter.setPen(QPen(Qt::white, 4));
    painter.setBrush(QColor(234, 67, 53));
    painter.drawEllipse(endPos, 14, 14);
    painter.setPen(Qt::white);
    painter.drawText(QRectF(endPos.x() - 14, endPos.y() - 14, 28, 28), Qt::AlignCenter, "B");
}

// --- MODIFIED FUNCTION ---
void MapWidget::drawTrafficLights(QPainter &painter)
{
    if (currentTrafficLights.isEmpty()) return;

    painter.setRenderHint(QPainter::Antialiasing, true);
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(10);
    painter.setFont(font);

    for (const auto& light : currentTrafficLights) {
        // --- NEW LOGIC ---
        // Only draw the light if it's RED and has vehicles QUEUED
        if (light.isGreen || light.queueSize == 0) {
            continue;
        }
        // --- END NEW LOGIC ---

        if (!currentGraph.hasNode(light.nodeId)) continue;

        Graph::Node node = currentGraph.getNode(light.nodeId);
        QPointF pos = geoToPixel(node.lat, node.lon);

        // Draw traffic light circle (smaller)
        QColor lightColor = QColor(244, 67, 54); // Always red if drawn

        painter.setPen(QPen(Qt::white, 2)); // Thinner pen
        painter.setBrush(lightColor);
        painter.drawEllipse(pos, 7, 7); // <-- Reduced size from 10 to 7

        // --- NEW: Draw Countdown Timer ---
        int countdown = qFloor(light.cycleDuration - light.timer);
        if (countdown < 0) countdown = 0;

        QRectF textRect(pos.x() - 15, pos.y() + 8, 30, 15);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 180));
        painter.drawRoundedRect(textRect, 3, 3);

        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(countdown));
        // --- END NEW ---
    }
}
// --- END MODIFIED FUNCTION ---

void MapWidget::drawVehicles(QPainter &painter)
{
    if (currentVehicles.isEmpty()) return;

    painter.setRenderHint(QPainter::Antialiasing, true);

    for (const auto& vehicle : currentVehicles) {
        // Vehicle position is in lon/lat format
        QPointF pos = geoToPixel(vehicle.position.y(), vehicle.position.x());

        // Draw vehicle as a colored circle
        QColor vehicleColor = vehicle.color;

        // Draw shadow
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 80));
        painter.drawEllipse(pos + QPointF(2, 2), 7, 7);

        // Draw vehicle body
        if (vehicle.isPriority) {
            // Priority vehicles (ambulances) are larger and red
            painter.setPen(QPen(Qt::white, 2));
            painter.setBrush(QColor(255, 0, 0));
            painter.drawEllipse(pos, 9, 9);

            // Draw cross symbol for ambulance
            painter.setPen(QPen(Qt::white, 2));
            painter.drawLine(pos + QPointF(-4, 0), pos + QPointF(4, 0));
            painter.drawLine(pos + QPointF(0, -4), pos + QPointF(0, 4));
        } else {
            // Regular vehicles
            painter.setPen(QPen(Qt::white, 1));
            painter.setBrush(vehicleColor);
            painter.drawEllipse(pos, 6, 6);
        }

        // Draw waiting indicator if stopped at light
        if (vehicle.waitingAtLight) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(255, 255, 0, 150));
            painter.drawEllipse(pos, 10, 10);
        }
    }
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(rect(), QColor("#2b2b2b"));

    // Draw map tiles
    drawTiles(painter);

    // Draw loaded area overlay
    drawLoadedAreaOverlay(painter);

    // Draw highlight box
    drawHighlight(painter);

    // Draw shortest path (if any)
    drawPath(painter);

    // Draw traffic lights
    drawTrafficLights(painter);
    drawReroutedPaths(painter);

    // Draw vehicles (on top of everything)
    drawVehicles(painter);

    // Draw info overlays
    painter.setPen(Qt::white);
    painter.setBrush(QColor(0, 0, 0, 200));

    // Zoom indicator
    QRect zoomBox(10, height() - 35, 100, 30);
    painter.drawRoundedRect(zoomBox, 5, 5);
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(zoomBox, Qt::AlignCenter, QString("Zoom: %1").arg(zoomLevel));

    // Status indicator
    QRect statusBox(width() - 160, height() - 35, 150, 30);
    painter.setBrush(QColor(0, 0, 0, 200));
    painter.drawRoundedRect(statusBox, 5, 5);
    painter.setPen(Qt::white);

    int loadedTiles = tileCache.size();
    int pendingCount = pendingTiles.size();
    QString statusText = pendingCount > 0
                             ? QString("Loading: %1/%2").arg(loadedTiles).arg(loadedTiles + pendingCount)
                             : QString("Tiles: %1").arg(loadedTiles);

    painter.drawText(statusBox, Qt::AlignCenter, statusText);

    // Vehicle count indicator (top right)
    if (!currentVehicles.isEmpty()) {
        QRect vehicleBox(width() - 160, 10, 150, 30);
        painter.setBrush(QColor(0, 0, 0, 200));
        painter.drawRoundedRect(vehicleBox, 5, 5);
        painter.setPen(Qt::white);
        painter.drawText(vehicleBox, Qt::AlignCenter,
                         QString("🚗 Vehicles: %1").arg(currentVehicles.size()));
    }
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isPanning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPanning) {
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();

        double pixelsPerTile = TILE_SIZE;
        double tilesAtZoom = pow(2.0, zoomLevel);
        double degreesLonPerPixel = 360.0 / (tilesAtZoom * pixelsPerTile);
        double currentLatRad = qDegreesToRadians(centerLat);
        double degreesLatPerPixel = (360.0 / (tilesAtZoom * pixelsPerTile)) / cos(currentLatRad);

        double newLon = centerLon - (delta.x() * degreesLonPerPixel);
        double newLat = centerLat + (delta.y() * degreesLatPerPixel);

        if (hasLoadedArea) {
            double latBuffer = (loadedAreaBounds.maxLat - loadedAreaBounds.minLat) * 0.10;
            double lonBuffer = (loadedAreaBounds.maxLon - loadedAreaBounds.minLon) * 0.10;

            double minLat = loadedAreaBounds.minLat - latBuffer;
            double maxLat = loadedAreaBounds.maxLat + latBuffer;
            double minLon = loadedAreaBounds.minLon - lonBuffer;
            double maxLon = loadedAreaBounds.maxLon + lonBuffer;

            if (newLat < minLat) newLat = minLat;
            if (newLat > maxLat) newLat = maxLat;
            if (newLon < minLon) newLon = minLon;
            if (newLon > maxLon) newLon = maxLon;
        } else {
            if (newLat < KARACHI_MIN_LAT) newLat = KARACHI_MIN_LAT;
            if (newLat > KARACHI_MAX_LAT) newLat = KARACHI_MAX_LAT;
            if (newLon < KARACHI_MIN_LON) newLon = KARACHI_MIN_LON;
            if (newLon > KARACHI_MAX_LON) newLon = KARACHI_MAX_LON;
        }

        centerLat = newLat;
        centerLon = newLon;
        update();
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();
    if (delta > 0) {
        zoomIn();
    } else if (delta < 0) {
        zoomOut();
    }
}

void MapWidget::zoomIn()
{
    if (zoomLevel < MAX_ZOOM) {
        zoomLevel++;
        qDebug() << "Zooming in to level:" << zoomLevel;
        update();
    }
}

void MapWidget::zoomOut()
{
    if (zoomLevel > MIN_ZOOM) {
        zoomLevel--;
        qDebug() << "Zooming out to level:" << zoomLevel;
        update();
    }
}

void MapWidget::resetView()
{
    updateCenter();
    zoomLevel = 13;
    qDebug() << "View reset - Center:" << centerLat << "," << centerLon;
    update();
}

void MapWidget::focusOnPath(const QList<qint64>& path)
{
    if (path.isEmpty()) return;

    double pathMinLat = 999, pathMaxLat = -999;
    double pathMinLon = 999, pathMaxLon = -999;

    for (qint64 nodeId : path) {
        const Graph::Node node = currentGraph.getNode(nodeId);
        if (node.lat < pathMinLat) pathMinLat = node.lat;
        if (node.lat > pathMaxLat) pathMaxLat = node.lat;
        if (node.lon < pathMinLon) pathMinLon = node.lon;
        if (node.lon > pathMaxLon) pathMaxLon = node.lon;
    }

    centerLat = (pathMinLat + pathMaxLat) / 2.0;
    centerLon = (pathMinLon + pathMaxLon) / 2.0;

    double latDiff = pathMaxLat - pathMinLat;
    double lonDiff = pathMaxLon - pathMinLon;

    int newZoom = 13;
    if (latDiff < 0.005 && lonDiff < 0.005) newZoom = 16;
    else if (latDiff < 0.01 && lonDiff < 0.01) newZoom = 15;
    else if (latDiff < 0.02 && lonDiff < 0.02) newZoom = 14;
    else if (latDiff < 0.05 && lonDiff < 0.05) newZoom = 13;
    else newZoom = 12;

    if (newZoom < MIN_ZOOM) newZoom = MIN_ZOOM;
    if (newZoom > MAX_ZOOM) newZoom = MAX_ZOOM;
    zoomLevel = newZoom;

    qDebug() << "Focused on path - Center:" << centerLat << "," << centerLon << "Zoom:" << zoomLevel;
    update();
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update();
}

void MapWidget::setHighlightArea(const BoundingBox& bounds)
{
    highlightArea = bounds;
    showHighlight = true;
    update();
}

void MapWidget::clearHighlight()
{
    if (showHighlight) {
        showHighlight = false;
        update();
    }
}

void MapWidget::setLoadedAreaBounds(const BoundingBox& bounds)
{
    loadedAreaBounds = bounds;
    hasLoadedArea = true;
    qDebug() << "Loaded area bounds set:" << bounds.minLat << bounds.minLon
             << "to" << bounds.maxLat << bounds.maxLon;
}
/**
 * @brief Draws the paths of vehicles that have been rerouted.
 *
 * This function iterates through all current vehicles and compares their
 * path segments against the original 'shortestPath'. Any segment
 * found in a vehicle's path that is NOT in the original path is
 * drawn in orange to highlight the diversion.
 */
/**
 * @brief Draws the paths of vehicles that have been rerouted.
 *
 * This function iterates through all current vehicles and compares their
 * path segments against the original 'm_shortestPath'. Any segment
 * found in a vehicle's path that is NOT in the original path is
 * drawn in orange to highlight the diversion.
 */
/**
 * @brief Draws the paths of vehicles that have been rerouted.
 *
 * This function iterates through all current vehicles and compares their
 * path segments against the original 'currentPath'. Any segment
 * found in a vehicle's path that is NOT in the original path is
 * drawn in orange to highlight the diversion.
 */
/**
 * @brief Draws the paths of vehicles that have been rerouted.
 *
 * This function iterates through all current vehicles and compares their
 * path segments against the original 'currentPath'. Any segment
 * found in a vehicle's path that is NOT in the original path is
 * drawn in orange to highlight the diversion.
 */
void MapWidget::drawReroutedPaths(QPainter &painter)
{
    // --- CORRECTED ---
    // Use 'getNodeCount() == 0' instead of 'isEmpty()'
    if ((currentGraph.getNodeCount() == 0) || currentVehicles.isEmpty() || currentPath.isEmpty()) {
        return; // Nothing to draw
    }

    // --- Create a set of the original path's edges for fast lookup ---
    // We store an edge as a single quint64 for efficiency.
    QSet<quint64> originalEdges;
    for (int i = 0; i < currentPath.size() - 1; ++i) {
        quint64 from = currentPath[i];
        quint64 to = currentPath[i+1];
        originalEdges.insert((from << 32) | to);
        originalEdges.insert((to << 32) | from); // For two-way matching
    }
    // ---

    // Define the pen for rerouted (diverted) paths
    // A solid, thick, bright orange line
    QPen reroutePen(QColor(0, 0, 0), 3.5, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(reroutePen);

    // Check each vehicle's path
    for (const auto& vehicle : currentVehicles) {
        if (vehicle.path.size() < 2) {
            continue; // Not a valid path
        }

        // Check each segment (edge) of this vehicle's current path
        for (int i = 0; i < vehicle.path.size() - 1; ++i) {
            qint64 fromNodeId = vehicle.path[i];
            qint64 toNodeId = vehicle.path[i+1];

            // Create the edge representations to check against the set
            quint64 edgeForward = (quint64(fromNodeId) << 32) | quint64(toNodeId);
            quint64 edgeReverse = (quint64(toNodeId) << 32) | quint64(fromNodeId);

            // If this edge is NOT in the original path, draw it in orange
            if (!originalEdges.contains(edgeForward) && !originalEdges.contains(edgeReverse)) {

                Graph::Node fromNode = currentGraph.getNode(fromNodeId);
                Graph::Node toNode = currentGraph.getNode(toNodeId);

                // Use 'geoToPixel' and pass lat/lon as separate doubles
                QPointF p1 = this->geoToPixel(fromNode.lat, fromNode.lon);
                QPointF p2 = this->geoToPixel(toNode.lat, toNode.lon);

                painter.drawLine(p1, p2);
            }
        }
    }
} // <-- CORRECTED: Make sure there is no 's' after this closing brace
