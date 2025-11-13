#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMap>
#include <QSet>
#include "graph.h"
#include "traffic_simulator.h"  // REQUIRED - Add this line

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    struct BoundingBox {
        double minLat, minLon, maxLat, maxLon;
    };

    explicit MapWidget(QWidget *parent = nullptr);

    void setGraphData(const Graph& graphData);
    void setShortestPath(const QList<qint64>& path);
    void clearPath();

    // Traffic visualization methods - ADD THESE THREE LINES
    void setVehicles(const QVector<TrafficSimulator::Vehicle>& vehicles);
    void setTrafficLights(const QVector<TrafficSimulator::TrafficLight>& lights);
    void clearTrafficVisualization();

public slots:
    void zoomIn();
    void zoomOut();
    void resetView();
    void focusOnPath(const QList<qint64>& path);

    // Highlight functions
    void setHighlightArea(const BoundingBox& bounds);
    void clearHighlight();
    void setLoadedAreaBounds(const BoundingBox& bounds);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onTileDownloaded(QNetworkReply *reply);

private:
    // Drawing functions
    void drawTiles(QPainter &painter);
    void drawGraph(QPainter &painter);
    void drawPath(QPainter &painter);
    void drawHighlight(QPainter &painter);
    void drawLoadedAreaOverlay(QPainter &painter);
    void drawTrafficLights(QPainter &painter);  // ADD THIS LINE
    void drawVehicles(QPainter &painter);       // ADD THIS LINE
    void drawReroutedPaths(QPainter &painter);

    // Coordinate conversion
    QPointF geoToPixel(double lat, double lon);
    QPointF latLonToTile(double lat, double lon, int zoom);
    double lon2tilex(double lon, int z);
    double lat2tiley(double lat, int z);
    double tilex2lon(int x, int z);
    double tiley2lat(int y, int z);

    // Tile management
    QString getTileKey(int x, int y, int z);
    void downloadTile(int x, int y, int z);

    // Helper functions
    void calculateBounds();
    void updateCenter();

    // Graph data
    Graph currentGraph;
    QList<qint64> currentPath;

    // Traffic simulation data - ADD THESE TWO LINES
    QVector<TrafficSimulator::Vehicle> currentVehicles;
    QVector<TrafficSimulator::TrafficLight> currentTrafficLights;

    // Map bounds
    double minLat, minLon, maxLat, maxLon;
    double centerLat, centerLon;

    // Zoom and pan
    int zoomLevel = 13;
    static constexpr int MIN_ZOOM = 11;
    static constexpr int MAX_ZOOM = 18;
    static constexpr int TILE_SIZE = 256;

    // Panning state
    bool isPanning = false;
    QPoint lastMousePos;

    // Tile caching
    QMap<QString, QPixmap> tileCache;
    QSet<QString> pendingTiles;
    QSet<QString> failedTiles;
    QNetworkAccessManager *networkManager;

    // Highlight box
    BoundingBox highlightArea;
    bool showHighlight = false;

    // Karachi boundaries (for global clamp)
    static constexpr double KARACHI_MIN_LAT = 24.75;
    static constexpr double KARACHI_MAX_LAT = 25.10;
    static constexpr double KARACHI_MIN_LON = 66.85;
    static constexpr double KARACHI_MAX_LON = 67.35;

    // Loaded area boundaries (for stricter pan locking)
    BoundingBox loadedAreaBounds;
    bool hasLoadedArea = false;
};

#endif // MAPWIDGET_H
