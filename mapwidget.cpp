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

    // Setup network manager for tile downloads with connection pooling
    networkManager = new QNetworkAccessManager(this);

    // CRITICAL: Enable HTTP/2 and pipelining for faster downloads
    networkManager->setAutoDeleteReplies(true);

    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MapWidget::onTileDownloaded);
}

void MapWidget::setGraphData(const Graph& graphData)
{
    currentGraph = graphData;
    clearPath();
    calculateBounds();
    updateCenter();

    // DON'T clear cache - it slows things down
    // tileCache.clear();

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
    offsetX = 0.0;
    offsetY = 0.0;
}

// Tile coordinate conversion functions
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

    double pixelX = (tile.x() - centerTile.x()) * TILE_SIZE + width() / 2.0 + offsetX;
    double pixelY = (tile.y() - centerTile.y()) * TILE_SIZE + height() / 2.0 + offsetY;

    return QPointF(pixelX, pixelY);
}

QString MapWidget::getTileKey(int x, int y, int z)
{
    return QString("%1_%2_%3").arg(z).arg(x).arg(y);
}

void MapWidget::downloadTile(int x, int y, int z)
{
    QString key = getTileKey(x, y, z);

    if (tileCache.contains(key)) {
        return; // Already cached
    }

    // Check if already downloading
    if (pendingTiles.contains(key)) {
        return;
    }
    pendingTiles.insert(key);

    // Try multiple tile servers for redundancy and speed
    // Using faster tile servers for better performance
    QStringList tileServers = {
        QString("https://tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://a.tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://b.tile.openstreetmap.org/%1/%2/%3.png"),
        QString("https://c.tile.openstreetmap.org/%1/%2/%3.png"),
        // Backup: CartoDB tiles (faster but different style)
        // QString("https://cartodb-basemaps-a.global.ssl.fastly.net/light_all/%1/%2/%3.png")
    };

    // Rotate through servers for load balancing
    static int serverIndex = 0;
    QString urlTemplate = tileServers[serverIndex % tileServers.size()];
    serverIndex++;

    QString url = urlTemplate.arg(z).arg(x).arg(y);

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    // Critical headers for OSM
    request.setRawHeader("User-Agent", "TrafficSimulatorKarachi/1.0 (Qt Application)");
    request.setRawHeader("Accept", "image/png,image/*;q=0.8,*/*;q=0.5");
    request.setRawHeader("Accept-Language", "en-US,en;q=0.9");
    request.setRawHeader("Connection", "keep-alive");

    // Speed optimizations
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                         QNetworkRequest::PreferCache); // Use cache first!
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setAttribute(QNetworkRequest::CacheSaveControlAttribute, true);

    // Set timeout
    request.setTransferTimeout(5000); // 5 second timeout

    QNetworkReply *reply = networkManager->get(request);
    reply->setProperty("tileKey", key);
    reply->setProperty("tileX", x);
    reply->setProperty("tileY", y);
    reply->setProperty("tileZ", z);

    qDebug() << "?? Downloading tile:" << key << "from" << url;
}

void MapWidget::onTileDownloaded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    QString key = reply->property("tileKey").toString();
    pendingTiles.remove(key);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        if (data.isEmpty()) {
            qWarning() << "??  Empty tile data for:" << key;
            reply->deleteLater();
            return;
        }

        QPixmap pixmap;
        if (pixmap.loadFromData(data)) {
            tileCache[key] = pixmap;
            qDebug() << "? Tile loaded:" << key << "Size:" << data.size() << "bytes";
            update(); // Redraw with new tile
        } else {
            qWarning() << "? Failed to create pixmap from tile data:" << key;
        }
    } else {
        qWarning() << "? Tile download failed:" << reply->error() << reply->errorString()
        << "for" << key;

        // Retry once on failure
        if (!failedTiles.contains(key)) {
            failedTiles.insert(key);
            pendingTiles.remove(key);

            int x = reply->property("tileX").toInt();
            int y = reply->property("tileY").toInt();
            int z = reply->property("tileZ").toInt();

            qDebug() << "?? Retrying tile:" << key;
            QTimer::singleShot(1000, this, [this, x, y, z]() {
                downloadTile(x, y, z);
            });
        }
    }

    reply->deleteLater();
}

void MapWidget::drawTiles(QPainter &painter)
{
    if (minLat == 0.0 && maxLat == 0.0) {
        // Draw placeholder with instructions
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

    // Draw tiles
    for (int dx = -tilesX/2; dx <= tilesX/2; ++dx) {
        for (int dy = -tilesY/2; dy <= tilesY/2; ++dy) {
            int tileX = centerTileX + dx;
            int tileY = centerTileY + dy;

            // Check valid tile range
            int maxTile = (1 << zoomLevel) - 1;
            if (tileX < 0 || tileX > maxTile || tileY < 0 || tileY > maxTile) {
                continue;
            }

            QString key = getTileKey(tileX, tileY, zoomLevel);

            double pixelX = (tileX - centerTile.x()) * TILE_SIZE + width() / 2.0 + offsetX;
            double pixelY = (tileY - centerTile.y()) * TILE_SIZE + height() / 2.0 + offsetY;

            if (tileCache.contains(key)) {
                // Draw the actual map tile
                painter.drawPixmap(QPointF(pixelX, pixelY), tileCache[key]);
            } else {
                // Draw placeholder while loading - make it look better
                painter.fillRect(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE),
                                 QColor(229, 227, 223)); // OSM background color
                painter.setPen(QPen(QColor(200, 200, 200), 1));
                painter.drawRect(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE));

                // Draw subtle loading indicator
                painter.setPen(QColor(170, 170, 170));
                QFont smallFont = painter.font();
                smallFont.setPointSize(9);
                painter.setFont(smallFont);
                painter.drawText(QRectF(pixelX, pixelY, TILE_SIZE, TILE_SIZE),
                                 Qt::AlignCenter, "?");

                // Download tile (limit concurrent downloads)
                if (pendingTiles.size() < 10) { // Max 10 concurrent
                    downloadTile(tileX, tileY, zoomLevel);
                }
            }
        }
    }
}

void MapWidget::drawGraph(QPainter &painter)
{
    // Don't draw the graph overlay - let the OSM tiles show the roads
    return;
}

void MapWidget::drawPath(QPainter &painter)
{
    if (currentPath.size() < 2) return;

    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw white border for path first
    painter.setPen(QPen(Qt::white, 14, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < currentPath.size() - 1; ++i) {
        const Graph::Node fromNode = currentGraph.getNode(currentPath[i]);
        const Graph::Node toNode = currentGraph.getNode(currentPath[i + 1]);

        QPointF start = geoToPixel(fromNode.lat, fromNode.lon);
        QPointF end = geoToPixel(toNode.lat, toNode.lon);

        painter.drawLine(start, end);
    }

    // Draw blue line on top
    painter.setPen(QPen(QColor(66, 133, 244), 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < currentPath.size() - 1; ++i) {
        const Graph::Node fromNode = currentGraph.getNode(currentPath[i]);
        const Graph::Node toNode = currentGraph.getNode(currentPath[i + 1]);

        QPointF start = geoToPixel(fromNode.lat, fromNode.lon);
        QPointF end = geoToPixel(toNode.lat, toNode.lon);

        painter.drawLine(start, end);
    }

    // Draw start marker
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
    painter.drawText(QRectF(startPos.x() - 14, startPos.y() - 14, 28, 28),
                     Qt::AlignCenter, "A");

    // Draw end marker
    const Graph::Node endNode = currentGraph.getNode(currentPath.last());
    QPointF endPos = geoToPixel(endNode.lat, endNode.lon);

    painter.setPen(QPen(Qt::white, 4));
    painter.setBrush(QColor(234, 67, 53));
    painter.drawEllipse(endPos, 14, 14);

    painter.setPen(Qt::white);
    painter.drawText(QRectF(endPos.x() - 14, endPos.y() - 14, 28, 28),
                     Qt::AlignCenter, "B");
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw map tiles
    drawTiles(painter);

    // Draw shortest path
    drawPath(painter);

    // Draw info overlay with better styling
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
        offsetX += delta.x();
        offsetY += delta.y();
        lastMousePos = event->pos();
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
        qDebug() << "?? Zooming in to level:" << zoomLevel;
        update();
    }
}

void MapWidget::zoomOut()
{
    if (zoomLevel > MIN_ZOOM) {
        zoomLevel--;
        qDebug() << "?? Zooming out to level:" << zoomLevel;
        update();
    }
}

void MapWidget::resetView()
{
    updateCenter();
    zoomLevel = 14;
    qDebug() << "?? View reset - Center:" << centerLat << "," << centerLon;
    update();
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update();
}
