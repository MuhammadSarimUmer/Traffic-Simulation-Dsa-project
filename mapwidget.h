#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QMap>
#include <QSet>  // ← Make sure this is here
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMouseEvent>
#include <QWheelEvent>
#include "graph.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    void setGraphData(const Graph& graphData);
    void setShortestPath(const QList<qint64>& path);
    void clearPath();
    void zoomIn();
    void zoomOut();
    void resetView();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onTileDownloaded();

private:
    // Graph data
    Graph currentGraph;
    QList<qint64> currentPath;

    // Map bounds
    double minLat = 0.0;
    double minLon = 0.0;
    double maxLat = 0.0;
    double maxLon = 0.0;
    double centerLat = 0.0;
    double centerLon = 0.0;

    // Zoom and pan
    int zoomLevel = 13;
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 18;
    double offsetX = 0.0;
    double offsetY = 0.0;

    // Mouse interaction
    bool isPanning = false;
    QPoint lastMousePos;

    // Tile management
    QNetworkAccessManager *networkManager;
    QMap<QString, QPixmap> tileCache;
    QSet<QString> pendingTiles;  // ← Add this
    QSet<QString> failedTiles;   // ← Add this
    const int TILE_SIZE = 256;

    // Helper functions
    void calculateBounds();
    QPointF geoToPixel(double lat, double lon);
    QPointF latLonToTile(double lat, double lon, int zoom);
    void downloadTile(int x, int y, int z);
    QString getTileKey(int x, int y, int z);
    void drawTiles(QPainter &painter);
    void drawGraph(QPainter &painter);
    void drawPath(QPainter &painter);
    void updateCenter();

    // Coordinate conversions
    double lon2tilex(double lon, int z);
    double lat2tiley(double lat, int z);
    double tilex2lon(int x, int z);
    double tiley2lat(int y, int z);
};

#endif // MAPWIDGET_H
