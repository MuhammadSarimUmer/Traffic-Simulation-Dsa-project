#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDebug> // <-- Added for logging

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mapLoader(new MapLoader(this))
    , mapLoaded(false)
    , mapVisualization(new MapWidget(this))
    , trafficSimulator(nullptr)
{
    ui->setupUi(this);

    // Set MapWidget as central widget
    setCentralWidget(mapVisualization);

    // Setup the route details text area
    setupRouteDetailsPanel();

    // Connect "Load Map" button
    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::onLoadMapAreaClicked);

    // Setup area dropdown
    setupAreaSelection();

    // Connect "Find Path" button
    connect(ui->findPathButton, &QPushButton::clicked, this, &MainWindow::onFindPathClicked);

    // Connect "Clear Path" button
    connect(ui->clearPathButton, &QPushButton::clicked, this, &MainWindow::onClearPathClicked);

    // Connect zoom control buttons
    connect(ui->zoomInButton, &QPushButton::clicked, mapVisualization, &MapWidget::zoomIn);
    connect(ui->zoomOutButton, &QPushButton::clicked, mapVisualization, &MapWidget::zoomOut);
    connect(ui->resetViewButton, &QPushButton::clicked, mapVisualization, &MapWidget::resetView);

    // Connect map loader signals
    connect(mapLoader, &MapLoader::mapDataReady, this, &MainWindow::onMapDataLoaded);
    connect(mapLoader, &MapLoader::mapLoadFailed, this, &MainWindow::onMapLoadFailed);

    // Connect area selection for highlighting
    connect(ui->areaSelectionCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::onAreaSelected);

    // Connect traffic simulator buttons
    connect(ui->startSimButton, &QPushButton::clicked, this, &MainWindow::onStartSimulationClicked);
    connect(ui->stopSimButton, &QPushButton::clicked, this, &MainWindow::onStopSimulationClicked);
    connect(ui->resetSimButton, &QPushButton::clicked, this, &MainWindow::onResetSimulationClicked);
    connect(ui->addVehicleButton, &QPushButton::clicked, this, &MainWindow::onAddVehicleClicked);
    connect(ui->addPriorityButton, &QPushButton::clicked, this, &MainWindow::onAddPriorityVehicleClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::onSimulationSpeedChanged);

    // Disable pathfinding UI until map loads
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);
    ui->findPathButton->setEnabled(false);
    ui->clearPathButton->setEnabled(false);

    // Disable traffic simulator UI until map loads
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(false);
    ui->resetSimButton->setEnabled(false);
    ui->addVehicleButton->setEnabled(false);
    ui->addPriorityButton->setEnabled(false);
    ui->simSourceCombo->setEnabled(false);
    ui->simDestCombo->setEnabled(false);
    ui->speedSlider->setEnabled(false);

    setWindowTitle("Traffic Control Simulator - Karachi");

    // Set status bar message
    statusBar()->showMessage("Ready. Select an area and click 'Load Map Area' to begin.");

    // Trigger highlight for the initially selected area
    onAreaSelected(ui->areaSelectionCombo->currentText());
}

MainWindow::~MainWindow()
{
    if (trafficSimulator) {
        trafficSimulator->stop();
        delete trafficSimulator;
    }
    delete ui;
}

void MainWindow::setupRouteDetailsPanel()
{
    if (ui->routeDetailsText) {
        ui->routeDetailsText->setReadOnly(true);
        ui->routeDetailsText->setStyleSheet(
            "QTextEdit {"
            "    background-color: #2b2b2b;"
            "    color: #ffffff;"
            "    border: 1px solid #444;"
            "    border-radius: 5px;"
            "    padding: 10px;"
            "    font-family: 'Segoe UI', Arial;"
            "    font-size: 11pt;"
            "}"
            );
        clearRouteDetails();
    }
}

void MainWindow::clearRouteDetails()
{
    if (ui->routeDetailsText) {
        ui->routeDetailsText->setHtml(
            "<div style='text-align: center; padding: 20px; color: #888;'>"
            "<h3 style='color: #aaa;'>📍 Route Details</h3>"
            "<p>Select source and destination, then click<br>"
            "<b>'Find Shortest Path'</b> to see directions here.</p>"
            "</div>"
            );
    }
}

void MainWindow::displayRouteDetails(const Graph::PathResult& result)
{
    if (!ui->routeDetailsText) return;

    QString html = QString(
                       "<div style='padding: 10px;'>"
                       "<h2 style='color: #4CAF50; margin: 0 0 10px 0;'>✅ Route Found</h2>"
                       "<div style='background: #1e1e1e; padding: 10px; border-radius: 5px; margin-bottom: 15px;'>"
                       "<p style='margin: 5px 0;'><b>📏 Distance:</b> <span style='color: #4CAF50;'>%1 km</span></p>"
                       "<p style='margin: 5px 0;'><b>📍 Stops:</b> <span style='color: #2196F3;'>%2</span></p>"
                       "</div>"
                       "<h3 style='color: #fff; margin: 15px 0 10px 0;'>Turn-by-Turn Directions:</h3>"
                       "<ol style='padding-left: 20px; margin: 0;'>"
                       ).arg(result.totalDistance, 0, 'f', 2).arg(result.path.size());

    double cumulativeDistance = 0.0;

    for (int i = 0; i < result.path.size(); ++i) {
        qint64 nodeId = result.path[i];
        const Graph::Node node = graph.getNode(nodeId);
        QString name = graph.getNodeDisplayName(nodeId);

        QString segmentInfo = "";
        if (i > 0) {
            qint64 prevNodeId = result.path[i - 1];
            const Graph::Node prevNode = graph.getNode(prevNodeId);
            double segmentDist = graph.haversineDistance(
                prevNode.lat, prevNode.lon,
                node.lat, node.lon
                );
            cumulativeDistance += segmentDist;

            int distanceMeters = qRound(segmentDist * 1000);
            segmentInfo = QString(" <span style='color: #888; font-style: italic;'>(%1 m)</span>")
                              .arg(distanceMeters);
        }

        QString stepHtml;
        if (i == 0) {
            stepHtml = QString(
                           "<li style='margin: 10px 0; padding: 8px; background: #1a3d1a; border-left: 4px solid #4CAF50; border-radius: 3px;'>"
                           "<b style='color: #4CAF50;'>START:</b> %1<br>"
                           "<small style='color: #888;'>Coordinates: %2, %3</small>"
                           "</li>"
                           ).arg(name).arg(node.lat, 0, 'f', 6).arg(node.lon, 0, 'f', 6);
        }
        else if (i == result.path.size() - 1) {
            stepHtml = QString(
                           "<li style='margin: 10px 0; padding: 8px; background: #3d1a1a; border-left: 4px solid #f44336; border-radius: 3px;'>"
                           "<b style='color: #f44336;'>END:</b> %1%2<br>"
                           "<small style='color: #888;'>Coordinates: %3, %4</small>"
                           "</li>"
                           ).arg(name).arg(segmentInfo).arg(node.lat, 0, 'f', 6).arg(node.lon, 0, 'f', 6);
        }
        else {
            stepHtml = QString(
                           "<li style='margin: 10px 0; padding: 8px; background: #1a2a3d; border-left: 4px solid #2196F3; border-radius: 3px;'>"
                           "<b style='color: #2196F3;'>Via:</b> %1%2<br>"
                           "<small style='color: #888;'>Coordinates: %3, %4</small>"
                           "</li>"
                           ).arg(name).arg(segmentInfo).arg(node.lat, 0, 'f', 6).arg(node.lon, 0, 'f', 6);
        }

        html += stepHtml;
    }

    html += "</ol></div>";

    ui->routeDetailsText->setHtml(html);

    QTextCursor cursor = ui->routeDetailsText->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->routeDetailsText->setTextCursor(cursor);
}

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

void MainWindow::onLoadMapAreaClicked()
{
    mapVisualization->clearPath();
    mapVisualization->setGraphData(Graph());
    mapVisualization->clearHighlight();
    mapVisualization->clearTrafficVisualization();
    clearRouteDetails();

    QString selectedArea = ui->areaSelectionCombo->currentText();
    if (!areaBounds.contains(selectedArea)) {
        QMessageBox::warning(this, "Error", "Please select a valid area.");
        return;
    }

    MapWidget::BoundingBox bounds = areaBounds[selectedArea];
    mapVisualization->setLoadedAreaBounds(bounds);

    ui->loadMapButton->setEnabled(false);
    ui->loadMapButton->setText("Loading...");
    ui->findPathButton->setEnabled(false);
    ui->clearPathButton->setEnabled(false);
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);

    statusBar()->showMessage(QString("Fetching map data for %1...").arg(selectedArea));

    QMessageBox::information(this, "Loading Map",
                             QString("Fetching map for %1.\n\nThis may take a moment. "
                                     "The map will load with interactive zoom and pan features!")
                                 .arg(selectedArea));

    mapLoader->fetchMapData(bounds.minLat, bounds.minLon, bounds.maxLat, bounds.maxLon);
}

void MainWindow::onMapDataLoaded(const QByteArray& data)
{
    bool success = graph.loadFromOverpassJSON(data);

    if (success && graph.getNodeCount() > 0 && graph.getEdgeCount() > 0) {
        mapLoaded = true;

        mapVisualization->setGraphData(graph);
        populateComboBoxes();

        ui->sourceCombo->setEnabled(true);
        ui->destCombo->setEnabled(true);
        ui->findPathButton->setEnabled(true);
        ui->clearPathButton->setEnabled(true);
        ui->loadMapButton->setText("Load Map Area");
        ui->loadMapButton->setEnabled(true);

        // Initialize traffic simulator
        setupTrafficSimulator();

        QString message = QString(
                              "✅ Map loaded successfully!\n\n"
                              "📍 Nodes: %1\n"
                              "🛣️  Edges: %2\n\n"
                              "You can now:\n"
                              "• Use mouse wheel to zoom in/out\n"
                              "• Click and drag to pan the map\n"
                              "• Select locations to find routes!\n"
                              "• Run traffic simulation!"
                              ).arg(graph.getNodeCount()).arg(graph.getEdgeCount());

        statusBar()->showMessage(QString("Map loaded: %1 nodes, %2 edges")
                                     .arg(graph.getNodeCount()).arg(graph.getEdgeCount()));

        QMessageBox::information(this, "Success", message);
    } else {
        onMapLoadFailed("Failed to parse map data or map is empty.");
    }
}

void MainWindow::onMapLoadFailed(const QString& error)
{
    ui->loadMapButton->setText("Load Map Area");
    ui->loadMapButton->setEnabled(true);
    statusBar()->showMessage("Map load failed");
    QMessageBox::critical(this, "Error",
                          QString("Failed to load map data.\n\nError: %1\n\n"
                                  "Please try a different area or check your internet connection.")
                              .arg(error));
}

void MainWindow::populateComboBoxes()
{
    ui->sourceCombo->clear();
    ui->destCombo->clear();
    ui->simSourceCombo->clear();
    ui->simDestCombo->clear();

    QList<Graph::NamedLocation> locations = graph.getNamedLocations();

    if (locations.isEmpty()) {
        qWarning() << "No named locations found.";
        ui->sourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->destCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->simSourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->simDestCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        return;
    }

    for (const Graph::NamedLocation& loc : locations) {
        ui->sourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->destCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->simSourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->simDestCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
    }

    statusBar()->showMessage(QString("Ready to find routes between %1 locations")
                                 .arg(locations.size()));
}

void MainWindow::onFindPathClicked()
{
    if (!mapLoaded) {
        QMessageBox::warning(this, "Warning", "Please load a map first!");
        return;
    }

    mapVisualization->clearPath();
    clearRouteDetails();

    qint64 sourceId = ui->sourceCombo->currentData().toLongLong();
    qint64 destId = ui->destCombo->currentData().toLongLong();

    if (sourceId <= 0 || destId <= 0) {
        QMessageBox::warning(this, "Warning", "Please select valid locations.");
        return;
    }

    if (sourceId == destId) {
        QMessageBox::information(this, "Same Location",
                                 "Source and destination are the same!");
        return;
    }

    statusBar()->showMessage("Calculating shortest path...");

    Graph::PathResult result = graph.aStar(sourceId, destId);

    if (!result.found) {
        statusBar()->showMessage("No path found");
        QMessageBox::warning(this, "Path Not Found", result.errorMessage);
        clearRouteDetails();
        return;
    }

    mapVisualization->setShortestPath(result.path);
    displayRouteDetails(result);
    mapVisualization->focusOnPath(result.path);

    statusBar()->showMessage(QString("Route found: %1 km, %2 stops")
                                 .arg(result.totalDistance, 0, 'f', 2)
                                 .arg(result.path.size()));

    QString summary = QString(
                          "✅ Route calculated!\n\n"
                          "📏 Distance: %1 km\n"
                          "📍 Stops: %2\n\n"
                          "View turn-by-turn directions in the sidebar.\n"
                          "Map has been focused on the route."
                          ).arg(result.totalDistance, 0, 'f', 2)
                          .arg(result.path.size());

    QMessageBox::information(this, "Route Found", summary);
}

void MainWindow::onClearPathClicked()
{
    mapVisualization->clearPath();
    clearRouteDetails();
    statusBar()->showMessage("Path cleared");
}

void MainWindow::onAreaSelected(const QString& areaName)
{
    if (areaBounds.contains(areaName)) {
        mapVisualization->setHighlightArea(areaBounds[areaName]);
    }
}

void MainWindow::setupTrafficSimulator()
{
    if (trafficSimulator) {
        trafficSimulator->stop();
        delete trafficSimulator;
    }

    trafficSimulator = new TrafficSimulator(&graph, this);

    // Connect simulator signals
    connect(trafficSimulator, &TrafficSimulator::vehiclesUpdated,
            this, &MainWindow::onVehiclesUpdated);
    connect(trafficSimulator, &TrafficSimulator::trafficLightsUpdated,
            this, &MainWindow::onTrafficLightsUpdated);
    connect(trafficSimulator, &TrafficSimulator::edgeCongestionUpdated,
            this, &MainWindow::onEdgeCongestionUpdated);

    // Enable simulator controls
    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    ui->resetSimButton->setEnabled(true);
    ui->addVehicleButton->setEnabled(true);
    ui->addPriorityButton->setEnabled(true);
    ui->simSourceCombo->setEnabled(true);
    ui->simDestCombo->setEnabled(true);
    ui->speedSlider->setEnabled(true);
    ui->speedSlider->setValue(10); // Default speed 1.0x

    ui->simStatsLabel->setText("Vehicles: 0 | Lights: 0 | Speed: 1.0x");
}

void MainWindow::onStartSimulationClicked()
{
    if (!trafficSimulator) return;

    trafficSimulator->start();
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(true);
    statusBar()->showMessage("Traffic simulation started");

    // --- NEW: Add a manual jam for demonstration ---
    // (This is a temporary hack to show the feature)
    if (ui->simSourceCombo->count() > 20) {
        // Find two different, valid nodes to create a jam
        qint64 from = ui->simSourceCombo->itemData(10).toLongLong();
        qint64 to = ui->simSourceCombo->itemData(11).toLongLong();

        if (from > 0 && to > 0 && from != to) {
            trafficSimulator->addManualJam(from, to);
            qDebug() << "--- MANUAL JAM ADDED between nodes" << from << "and" << to << "---";
            QMessageBox::information(this, "Traffic Jam Added",
                                     QString("A static traffic jam has been created between %1 and %2 to demonstrate rerouting.")
                                         .arg(ui->simSourceCombo->itemText(10))
                                         .arg(ui->simSourceCombo->itemText(11)));
        } else {
            qDebug() << "--- Could not add manual jam (not enough nodes) ---";
        }
    }
    // --- END NEW ---
}

void MainWindow::onStopSimulationClicked()
{
    if (!trafficSimulator) return;

    trafficSimulator->stop();
    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    statusBar()->showMessage("Traffic simulation stopped");
}

void MainWindow::onResetSimulationClicked()
{
    if (!trafficSimulator) return;

    trafficSimulator->stop();
    trafficSimulator->reset();
    mapVisualization->clearTrafficVisualization();

    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    ui->simStatsLabel->setText("Vehicles: 0 | Lights: 0 | Speed: 1.0x");

    statusBar()->showMessage("Traffic simulation reset");
}

void MainWindow::onAddVehicleClicked()
{
    if (!trafficSimulator) return;

    qint64 source = ui->simSourceCombo->currentData().toLongLong();
    qint64 dest = ui->simDestCombo->currentData().toLongLong();

    if (source <= 0 || dest <= 0) {
        QMessageBox::warning(this, "Invalid Selection", "Please select valid source and destination.");
        return;
    }

    if (source == dest) {
        QMessageBox::warning(this, "Same Location", "Source and destination cannot be the same.");
        return;
    }

    trafficSimulator->addVehicle(source, dest, false);
    statusBar()->showMessage("Regular vehicle added");
}

void MainWindow::onAddPriorityVehicleClicked()
{
    if (!trafficSimulator) return;

    qint64 source = ui->simSourceCombo->currentData().toLongLong();
    qint64 dest = ui->simDestCombo->currentData().toLongLong();

    if (source <= 0 || dest <= 0) {
        QMessageBox::warning(this, "Invalid Selection", "Please select valid source and destination.");
        return;
    }

    if (source == dest) {
        QMessageBox::warning(this, "Same Location", "Source and destination cannot be the same.");
        return;
    }

    trafficSimulator->addVehicle(source, dest, true);
    statusBar()->showMessage("Priority vehicle (ambulance) added");
}

// --- MODIFIED ---
void MainWindow::onSimulationSpeedChanged(int value)
{
    if (!trafficSimulator) return;

    // Slider value 0-20 maps to speed 0.5x - 2.5x
    double speed = 0.5 + (value / 10.0);
    trafficSimulator->setSimulationSpeed(speed); // <-- Actually set the speed
    updateSimulationStats(); // <-- Update the label
}

void MainWindow::onVehiclesUpdated(const QVector<TrafficSimulator::Vehicle>& vehicles)
{
    mapVisualization->setVehicles(vehicles);
    updateSimulationStats(); // <-- Update stats when vehicles update
}
// --- END MODIFIED ---

void MainWindow::onTrafficLightsUpdated(const QVector<TrafficSimulator::TrafficLight>& lights)
{
    mapVisualization->setTrafficLights(lights);
    updateSimulationStats(); // <-- Update stats when lights update
}

void MainWindow::onEdgeCongestionUpdated(qint64 from, qint64 to, const QString& status)
{
    // You could visualize this in the status bar or a separate panel
    // For now, just log it
    //qDebug() << "Edge" << from << "->" << to << "status:" << status;
}

// --- MODIFIED ---
void MainWindow::updateSimulationStats()
{
    if (!trafficSimulator) return;

    // Use the new getter methods
    int vehicleCount = trafficSimulator->getVehicleCount();
    int lightCount = trafficSimulator->getTrafficLightCount();
    double speed = 0.5 + (ui->speedSlider->value() / 10.0);

    ui->simStatsLabel->setText(QString("Vehicles: %1 | Lights: %2 | Speed: %3x")
                                   .arg(vehicleCount)
                                   .arg(lightCount)
                                   .arg(speed, 0, 'f', 1));
}
// --- END MODIFIED ---

void MainWindow::showDetailedRoute(const Graph::PathResult& result)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Route Details");
    dialog->setMinimumSize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *header = new QLabel(QString(
                                    "<h2>Route Found</h2>"
                                    "<p><b>Distance:</b> %1 km | <b>Stops:</b> %2</p>"
                                    ).arg(result.totalDistance, 0, 'f', 3).arg(result.path.size()));
    header->setWordWrap(true);
    layout->addWidget(header);

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setReadOnly(true);

    QString directions = "<h3>Turn-by-Turn Directions:</h3><ol>";

    double cumulativeDistance = 0.0;

    for (int i = 0; i < result.path.size(); ++i) {
        qint64 nodeId = result.path[i];
        const Graph::Node node = graph.getNode(nodeId);
        QString name = graph.getNodeDisplayName(nodeId);

        QString segmentInfo = "";
        if (i > 0) {
            qint64 prevNodeId = result.path[i - 1];
            const Graph::Node prevNode = graph.getNode(prevNodeId);
            double segmentDist = graph.haversineDistance(
                prevNode.lat, prevNode.lon,
                node.lat, node.lon
                );
            cumulativeDistance += segmentDist;
            segmentInfo = QString(" <i>(%1 m)</i>").arg(qRound(segmentDist * 1000));
        }

        if (i == 0) {
            directions += QString("<li><b>START:</b> %1<br><small>Coordinates: %2, %3</small></li>")
            .arg(name)
                .arg(node.lat, 0, 'f', 6)
                .arg(node.lon, 0, 'f', 6);
        } else if (i == result.path.size() - 1) {
            directions += QString("<li><b>END:</b> %1%2<br><small>Coordinates: %3, %4</small></li>")
            .arg(name)
                .arg(segmentInfo)
                .arg(node.lat, 0, 'f', 6)
                .arg(node.lon, 0, 'f', 6);
        } else {
            directions += QString("<li><b>Via:</b> %1%2<br><small>Coordinates: %3, %4</small></li>")
            .arg(name)
                .arg(segmentInfo)
                .arg(node.lat, 0, 'f', 6)
                .arg(node.lon, 0, 'f', 6);
        }
    }

    directions += "</ol>";
    textEdit->setHtml(directions);
    layout->addWidget(textEdit);

    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->exec();
    delete dialog;
}
