#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "graph.h"
#include "map_loader.h"
#include "mapwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Struct for Area Bounds
struct BoundingBox {
    double minLat;
    double minLon;
    double maxLat;
    double maxLon;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadMapAreaClicked();
    void onFindPathClicked();
    void onMapDataLoaded(const QByteArray& data);
    void onMapLoadFailed(const QString& error);
    void onClearPathClicked();

private:
    void setupAreaSelection();
    void populateComboBoxes();
    void showDetailedRoute(const Graph::PathResult& result);

    // New methods for sidebar
    void setupRouteDetailsPanel();
    void displayRouteDetails(const Graph::PathResult& result);
    void clearRouteDetails();

    Ui::MainWindow *ui;
    Graph graph;
    MapLoader *mapLoader;
    bool mapLoaded;
    QMap<QString, BoundingBox> areaBounds;

    // Map Visualization Widget
    MapWidget *mapVisualization;
};

#endif // MAINWINDOW_H
