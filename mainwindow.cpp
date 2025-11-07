#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mapLoader(new MapLoader(this))
    , mapLoaded(false)
{
    ui->setupUi(this);

    // Connect "Load Map" button
    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::onLoadMapAreaClicked);

    // Setup area dropdown
    setupAreaSelection();

    // Connect "Find Path" button
    connect(ui->findPathButton, &QPushButton::clicked, this, &MainWindow::onFindPathClicked);

    // Connect map loader signals
    connect(mapLoader, &MapLoader::mapDataReady, this, &MainWindow::onMapDataLoaded);
    connect(mapLoader, &MapLoader::mapLoadFailed, this, &MainWindow::onMapLoadFailed);

    // Disable pathfinding UI until map loads
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);
    ui->findPathButton->setEnabled(false);

    setWindowTitle("Traffic Control Simulator - Karachi");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Fill the area dropdown with all Karachi districts ---
void MainWindow::setupAreaSelection()
{
    ui->areaSelectionCombo->clear();
    areaBounds.clear();

    // Karachi South
    areaBounds.insert("Karachi South (Saddar)", {24.8450, 67.0100, 24.8750, 67.0450});
    areaBounds.insert("Karachi South (Clifton)", {24.8000, 67.0200, 24.8400, 67.0700});
    areaBounds.insert("Karachi South (DHA)", {24.7900, 67.0400, 24.8500, 67.1200});

    // Karachi Central
    areaBounds.insert("Karachi Central (N. Nazimabad)", {24.9100, 67.0200, 24.9550, 67.0600});
    areaBounds.insert("Karachi Central (Gulberg)", {24.9000, 67.0500, 24.9500, 67.0800});
    areaBounds.insert("Karachi Central (Liaquatabad)", {24.8800, 67.0300, 24.9100, 67.0600});
    areaBounds.insert("Karachi Central (North Karachi)", {24.9500, 67.0600, 25.0100, 67.1100});
    areaBounds.insert("Karachi Central (New Karachi)", {24.9600, 67.0100, 25.0200, 67.0600});

    // Karachi East
    areaBounds.insert("Karachi East (Gulshan-e-Iqbal)", {24.8950, 67.0650, 24.9450, 67.1200});
    areaBounds.insert("Karachi East (Gulistan-e-Jauhar)", {24.8800, 67.1000, 24.9400, 67.1600});
    areaBounds.insert("Karachi East (Scheme 33 / Safoora)", {24.9400, 67.1200, 25.0200, 67.2000});

    // Malir
    areaBounds.insert("Malir (Airport / Malir Town)", {24.8700, 67.1700, 24.9500, 67.2500});

    // Korangi
    areaBounds.insert("Korangi (Korangi Town)", {24.8000, 67.1000, 24.8700, 67.1700});
    areaBounds.insert("Korangi (Landhi / Bin Qasim Port)", {24.8000, 67.1600, 24.8800, 67.2800});

    // Karachi West
    areaBounds.insert("Karachi West (Kemari / Mauripur)", {24.8200, 66.9500, 24.8700, 67.0100});
    areaBounds.insert("Karachi West (Baldia Town)", {24.8900, 66.9200, 24.9400, 66.9800});
    areaBounds.insert("Karachi West (SITE Area)", {24.8800, 66.9800, 24.9300, 67.0300});
    areaBounds.insert("Karachi West (Orangi Town)", {24.8900, 66.9500, 24.9600, 67.0200});

    ui->areaSelectionCombo->addItems(areaBounds.keys());
}

// --- Load Map Button ---
void MainWindow::onLoadMapAreaClicked()
{
    QString selectedArea = ui->areaSelectionCombo->currentText();
    if (!areaBounds.contains(selectedArea)) {
        QMessageBox::warning(this, "Error", "Please select a valid area.");
        return;
    }

    BoundingBox bounds = areaBounds[selectedArea];

    ui->loadMapButton->setEnabled(false);
    ui->loadMapButton->setText("Loading...");
    ui->findPathButton->setEnabled(false);
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);

    QMessageBox::information(this, "Loading Map",
                             QString("Fetching map for %1. This may take a moment...").arg(selectedArea));

    mapLoader->fetchMapData(bounds.minLat, bounds.minLon, bounds.maxLat, bounds.maxLon);
}

// --- Map Load Success ---
void MainWindow::onMapDataLoaded(const QByteArray& data)
{
    bool success = graph.loadFromOverpassJSON(data);

    if (success && graph.getNodeCount() > 0 && graph.getEdgeCount() > 0) {
        mapLoaded = true;
        populateComboBoxes();

        ui->sourceCombo->setEnabled(true);
        ui->destCombo->setEnabled(true);
        ui->findPathButton->setEnabled(true);
        ui->loadMapButton->setText("Load Map Area");
        ui->loadMapButton->setEnabled(true);

        QString message = QString(
                              "✅ Map loaded successfully!\n\n"
                              "Nodes: %1\nEdges: %2\n\nSelect locations to find routes!"
                              ).arg(graph.getNodeCount()).arg(graph.getEdgeCount());

        QMessageBox::information(this, "Success", message);
    } else {
        onMapLoadFailed("Failed to parse map data or map is empty.");
    }
}

// --- Map Load Failure ---
void MainWindow::onMapLoadFailed(const QString& error)
{
    ui->loadMapButton->setText("Load Map Area");
    ui->loadMapButton->setEnabled(true);
    QMessageBox::critical(this, "Error", "Failed to load map data.\nError: " + error);
}

// --- Populate source/destination dropdowns ---
void MainWindow::populateComboBoxes()
{
    ui->sourceCombo->clear();
    ui->destCombo->clear();

    QList<Graph::NamedLocation> locations = graph.getNamedLocations();

    if (locations.isEmpty()) {
        qWarning() << "No named locations found.";
        ui->sourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->destCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        return;
    }

    for (const Graph::NamedLocation& loc : locations) {
        ui->sourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->destCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
    }
}

// --- Pathfinding button ---
void MainWindow::onFindPathClicked()
{
    if (!mapLoaded) {
        QMessageBox::warning(this, "Warning", "Please load a map first!");
        return;
    }

    qint64 sourceId = ui->sourceCombo->currentData().toLongLong();
    qint64 destId = ui->destCombo->currentData().toLongLong();

    if (sourceId <= 0 || destId <= 0) {
        QMessageBox::warning(this, "Warning", "Please select valid locations.");
        return;
    }

    if (sourceId == destId) {
        QMessageBox::information(this, "Same Location", "Source and destination are the same!");
        return;
    }

    Graph::PathResult result = graph.aStar(sourceId, destId);

    if (!result.found) {
        QMessageBox::warning(this, "Path Not Found", result.errorMessage);
        return;
    }

    QString pathStr = "Route:\n\n";
    for (int i = 0; i < result.path.size(); ++i) {
        qint64 nodeId = result.path[i];
        QString name = graph.getNodeDisplayName(nodeId);

        if (i == 0) pathStr += QString("🚩 START: %1\n").arg(name);
        else if (i == result.path.size() - 1) pathStr += QString("🏁 END: %1\n").arg(name);
        else pathStr += QString("   ↓ Via: %1\n").arg(name);
    }

    QString message = QString(
                          "✅ Shortest path found!\n\n"
                          "📏 Distance: %1 km\n"
                          "📍 Stops: %2\n\n%3"
                          ).arg(result.totalDistance, 0, 'f', 3).arg(result.path.size()).arg(pathStr);

    QMessageBox::information(this, "Route Found", message);
}
