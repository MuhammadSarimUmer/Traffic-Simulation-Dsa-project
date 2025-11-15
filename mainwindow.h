#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map_loader.h"
#include "graph.h"
#include "mapwidget.h"
#include "traffic_simulator.h"
#include "database_manager.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // --- MODIFIED CONSTRUCTOR ---
    explicit MainWindow(DatabaseManager *dbManager, const QString& username, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Map loading slots
    void onLoadMapAreaClicked();
    void onMapDataLoaded(const QByteArray& data);
    void onMapLoadFailed(const QString& error);

    // Pathfinding slots
    void onFindPathClicked();
    void onClearPathClicked();
    void showDetailedRoute(const Graph::PathResult& result);
    void onAreaSelected(const QString& areaName);

    // Traffic simulator slots
    void onStartSimulationClicked();
    void onStopSimulationClicked();
    void onResetSimulationClicked();
    void onAddVehicleClicked();
    void onAddPriorityVehicleClicked();
    void onSimulationSpeedChanged(int value);

    // --- NEW SLOT FOR MANUAL JAMS ---
    void onAddJamClicked();
    // --- END NEW SLOT ---

    // Simulator update slots
    void onVehiclesUpdated(const QVector<TrafficSimulator::Vehicle>& vehicles);
    void onTrafficLightsUpdated(const QVector<TrafficSimulator::TrafficLight>& lights);
    void onEdgeCongestionUpdated(qint64 from, qint64 to, const QString& status);

    void onPathSourceChanged(int index);
    void onPathDestChanged(int index);

    // --- SLOTS FOR TOOLBAR BUTTONS ---
    void on_actionBackToLogin_triggered();
    void on_actionChat_triggered();

private:
    void setupAreaSelection();
    void populateComboBoxes();
    void setupRouteDetailsPanel();
    void clearRouteDetails();
    void displayRouteDetails(const Graph::PathResult& result);

    // Traffic simulator setup
    void setupTrafficSimulator();
    void updateSimulationStats();

    Ui::MainWindow *ui;
    MapLoader *mapLoader;
    bool mapLoaded;
    MapWidget *mapVisualization;
    Graph graph;
    DatabaseManager *dbManager;

    // Traffic simulator
    TrafficSimulator *trafficSimulator;

    QMap<QString, MapWidget::BoundingBox> areaBounds;

    // --- NEW MEMBER VARIABLES ---
    QString m_currentUsername;
    QString m_currentUserEmail;
};

#endif // MAINWINDOW_H
