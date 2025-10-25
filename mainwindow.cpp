#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mapLoaded(false)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::onLoadMapClicked);
    connect(ui->findPathButton, &QPushButton::clicked, this, &MainWindow::onFindPathClicked);

    // Disable pathfinding UI until map is loaded
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);
    ui->findPathButton->setEnabled(false);

    setWindowTitle("Traffic Control Simulator - Map & Graph Module");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadMapClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select OpenStreetMap File",
        QDir::currentPath(),
        "OSM Files (*.osm);;All Files (*)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    QMessageBox::information(this, "Loading", "Parsing map data, please wait...");

    bool success = graph.loadFromOSM(filePath);

    if (success) {
        mapLoaded = true;

        // Populate combo boxes with location names
        ui->sourceCombo->clear();
        ui->destCombo->clear();

        QList<Graph::NamedLocation> locations = graph.getNamedLocations();

        for (const Graph::NamedLocation& loc : locations) {
            ui->sourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
            ui->destCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        }

        // Enable pathfinding UI
        ui->sourceCombo->setEnabled(true);
        ui->destCombo->setEnabled(true);
        ui->findPathButton->setEnabled(true);

        QString message = QString(
                              "✅ Map loaded successfully!\n\n"
                              "Nodes: %1\n"
                              "Edges: %2\n\n"
                              "Select locations from dropdowns to find routes!"
                              ).arg(graph.getNodeCount()).arg(graph.getEdgeCount());

        QMessageBox::information(this, "Success", message);
    } else {
        QMessageBox::critical(this, "Error", "Failed to load map. Please check the file format.");
    }
}

void MainWindow::onFindPathClicked()
{
    if (!mapLoaded) {
        QMessageBox::warning(this, "Warning", "Please load a map first!");
        return;
    }

    // Get selected node IDs from combo boxes
    qint64 sourceId = ui->sourceCombo->currentData().toLongLong();
    qint64 destId = ui->destCombo->currentData().toLongLong();

    if (sourceId == destId) {
        QMessageBox::information(this, "Same Location",
                                 "Source and destination are the same!");
        return;
    }

    // Run Dijkstra's algorithm
    Graph::PathResult result = graph.dijkstra(sourceId, destId);

    if (!result.found) {
        QMessageBox::warning(this, "Path Not Found", result.errorMessage);
        return;
    }

    // Build path string with location names
    QString pathStr = "Route:\n\n";
    for (int i = 0; i < result.path.size(); ++i) {
        qint64 nodeId = result.path[i];
        QString locationName = graph.getNodeDisplayName(nodeId);

        if (i == 0) {
            pathStr += QString("🚩 START: %1\n").arg(locationName);
        } else if (i == result.path.size() - 1) {
            pathStr += QString("🏁 END: %1\n").arg(locationName);
        } else {
            pathStr += QString("   ↓ Via: %1\n").arg(locationName);
        }
    }

    // Show result
    QString message = QString(
                          "✅ Shortest path found!\n\n"
                          "📏 Total Distance: %1 km\n"
                          "📍 Stops: %2 intersections\n\n"
                          "%3"
                          ).arg(result.totalDistance, 0, 'f', 3)
                          .arg(result.path.size())
                          .arg(pathStr);

    QMessageBox::information(this, "Route Found", message);
}
