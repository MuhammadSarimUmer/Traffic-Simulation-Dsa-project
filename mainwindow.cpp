#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_dialog.h"
#include "incidentfeeddialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDebug>
#include <QCompleter>

// --- MODIFIED CONSTRUCTOR ---
MainWindow::MainWindow(DatabaseManager *dbManager, const QString& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mapLoader(new MapLoader(this))
    , mapLoaded(false)
    , mapVisualization(new MapWidget(this))
    , trafficSimulator(nullptr)
    , dbManager(dbManager)
    , m_currentUsername(username)
{
    ui->setupUi(this);

    if (dbManager) {
        m_currentUserEmail = dbManager->getEmailForUsername(m_currentUsername);
    }

    // --- MODIFICATION FOR SCROLL AREA ---
    // Add the map widget to the layout INSIDE the scroll area
    ui->mapLayout->addWidget(mapVisualization);
    // --- END MODIFICATION ---

    setupRouteDetailsPanel();

    auto makeSearchable = [](QComboBox* combo) {
        combo->setEditable(true);
        combo->setInsertPolicy(QComboBox::NoInsert);
        combo->completer()->setFilterMode(Qt::MatchContains);
        combo->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    };

    makeSearchable(ui->sourceCombo);
    makeSearchable(ui->destCombo);
    makeSearchable(ui->simSourceCombo);
    makeSearchable(ui->simDestCombo);
    makeSearchable(ui->jamSourceCombo);
    makeSearchable(ui->jamDestCombo);

    connect(ui->sourceCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::onPathSourceChanged);
    connect(ui->destCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::onPathDestChanged);

    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::onLoadMapAreaClicked);
    setupAreaSelection();
    connect(ui->findPathButton, &QPushButton::clicked, this, &MainWindow::onFindPathClicked);
    connect(ui->clearPathButton, &QPushButton::clicked, this, &MainWindow::onClearPathClicked);

    // --- Connect Reroute Button ---
    connect(ui->rerouteButton, &QPushButton::clicked, this, &MainWindow::onRerouteClicked);

    connect(ui->zoomInButton, &QPushButton::clicked, mapVisualization, &MapWidget::zoomIn);
    connect(ui->zoomOutButton, &QPushButton::clicked, mapVisualization, &MapWidget::zoomOut);
    connect(ui->resetViewButton, &QPushButton::clicked, mapVisualization, &MapWidget::resetView);

    connect(mapLoader, &MapLoader::mapDataReady, this, &MainWindow::onMapDataLoaded);
    connect(mapLoader, &MapLoader::mapLoadFailed, this, &MainWindow::onMapLoadFailed);
    connect(ui->areaSelectionCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::onAreaSelected);

    connect(ui->startSimButton, &QPushButton::clicked, this, &MainWindow::onStartSimulationClicked);
    connect(ui->stopSimButton, &QPushButton::clicked, this, &MainWindow::onStopSimulationClicked);
    connect(ui->resetSimButton, &QPushButton::clicked, this, &MainWindow::onResetSimulationClicked);
    connect(ui->addVehicleButton, &QPushButton::clicked, this, &MainWindow::onAddVehicleClicked);
    connect(ui->addPriorityButton, &QPushButton::clicked, this, &MainWindow::onAddPriorityVehicleClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::onSimulationSpeedChanged);
    connect(ui->addJamButton, &QPushButton::clicked, this, &MainWindow::onAddJamClicked);

    // Disable pathfinding UI until map loads
    ui->sourceCombo->setEnabled(false);
    ui->destCombo->setEnabled(false);
    ui->findPathButton->setEnabled(false);
    ui->clearPathButton->setEnabled(false);
    ui->rerouteButton->setEnabled(false); // <-- Disable reroute button

    // Disable traffic simulator UI until map loads
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(false);
    ui->resetSimButton->setEnabled(false);
    ui->addVehicleButton->setEnabled(false);
    ui->addPriorityButton->setEnabled(false);
    ui->simSourceCombo->setEnabled(false);
    ui->simDestCombo->setEnabled(false);
    ui->speedSlider->setEnabled(false);
    ui->jamSourceCombo->setEnabled(false);
    ui->jamDestCombo->setEnabled(false);
    ui->addJamButton->setEnabled(false);

    setWindowTitle("Traffic Control Simulator - Karachi");
    statusBar()->showMessage("Ready. Select an area and click 'Load Map Area' to begin.");
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
    areaBounds.insert("Karachi South (Saddar)", {24.8450, 67.0100, 24.8750, 67.0450});
    areaBounds.insert("Karachi South (Clifton)", {24.8000, 67.0200, 24.8400, 67.0700});
    areaBounds.insert("Karachi South (DHA)", {24.7900, 67.0400, 24.8500, 67.1200});
    areaBounds.insert("Karachi Central (N. Nazimabad)", {24.9100, 67.0200, 24.9550, 67.0600});
    areaBounds.insert("Karachi Central (Gulberg)", {24.9000, 67.0500, 24.9500, 67.0800});
    areaBounds.insert("Karachi Central (Liaquatabad)", {24.8800, 67.0300, 24.9100, 67.0600});
    areaBounds.insert("Karachi Central (North Karachi)", {24.9500, 67.0600, 25.0100, 67.1100});
    areaBounds.insert("Karachi Central (New Karachi)", {24.9600, 67.0100, 25.0200, 67.0600});
    areaBounds.insert("Karachi East (Gulshan-e-Iqbal)", {24.8950, 67.0650, 24.9450, 67.1200});
    areaBounds.insert("Karachi East (Gulistan-e-Jauhar)", {24.8800, 67.1000, 24.9400, 67.1600});
    areaBounds.insert("Karachi East (Scheme 33 / Safoora)", {24.9400, 67.1200, 25.0200, 67.2000});
    areaBounds.insert("Malir (Airport / Malir Town)", {24.8700, 67.1700, 24.9500, 67.2500});
    areaBounds.insert("Korangi (Korangi Town)", {24.8000, 67.1000, 24.8700, 67.1700});
    areaBounds.insert("Korangi (Landhi / Bin Qasim Port)", {24.8000, 67.1600, 24.8800, 67.2800});
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

    // --- Disable reroute button and clear path ---
    ui->rerouteButton->setEnabled(false);
    m_currentPath = Graph::PathResult();
    // ---

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

        setupTrafficSimulator();

        ui->jamSourceCombo->setEnabled(true);
        ui->jamDestCombo->setEnabled(true);
        ui->addJamButton->setEnabled(true);

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
    ui->jamSourceCombo->clear();
    ui->jamDestCombo->clear();

    QList<Graph::NamedLocation> locations = graph.getNamedLocations();

    if (locations.isEmpty()) {
        qWarning() << "No named locations found.";
        ui->sourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->destCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->simSourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->simDestCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->jamSourceCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        ui->jamDestCombo->addItem("No locations found", QVariant::fromValue(qint64(-1)));
        return;
    }

    for (const Graph::NamedLocation& loc : locations) {
        ui->sourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->destCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->simSourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->simDestCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->jamSourceCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
        ui->jamDestCombo->addItem(loc.displayName, QVariant::fromValue(loc.nodeId));
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

    QSet<QPair<qint64, qint64>> jams;
    if (trafficSimulator) {
        jams = trafficSimulator->getManualJams();
    }
    Graph::PathResult result = graph.aStar(sourceId, destId, jams);

    if (!result.found) {
        statusBar()->showMessage("No path found");
        QMessageBox::warning(this, "Path Not Found", result.errorMessage);
        clearRouteDetails();
        ui->rerouteButton->setEnabled(false); // <-- Disable reroute
        m_currentPath = Graph::PathResult(); // <-- Clear path
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

    // --- Enable reroute button and save the path ---
    m_currentPath = result;
    ui->rerouteButton->setEnabled(true);
    // ---
}

void MainWindow::onClearPathClicked()
{
    mapVisualization->clearPath();
    clearRouteDetails();
    statusBar()->showMessage("Path cleared");

    // --- Disable reroute button and clear path ---
    ui->rerouteButton->setEnabled(false);
    m_currentPath = Graph::PathResult();
    // ---
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

    connect(trafficSimulator, &TrafficSimulator::vehiclesUpdated,
            this, &MainWindow::onVehiclesUpdated);
    connect(trafficSimulator, &TrafficSimulator::trafficLightsUpdated,
            this, &MainWindow::onTrafficLightsUpdated);
    connect(trafficSimulator, &TrafficSimulator::edgeCongestionUpdated,
            this, &MainWindow::onEdgeCongestionUpdated);

    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    ui->resetSimButton->setEnabled(true);
    ui->addVehicleButton->setEnabled(true);
    ui->addPriorityButton->setEnabled(true);
    ui->simSourceCombo->setEnabled(true);
    ui->simDestCombo->setEnabled(true);
    ui->speedSlider->setEnabled(true);
    ui->speedSlider->setValue(10);

    ui->simStatsLabel->setText("Vehicles: 0 | Lights: 0 | Speed: 1.0x");
}

void MainWindow::onStartSimulationClicked()
{
    if (!trafficSimulator) return;

    trafficSimulator->start();
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(true);
    statusBar()->showMessage("Traffic simulation started");
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
    mapVisualization->setManualJams(QSet<QPair<qint64, qint64>>());

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

void MainWindow::onSimulationSpeedChanged(int value)
{
    if (!trafficSimulator) return;
    double speed = 0.5 + (value / 10.0);
    trafficSimulator->setSimulationSpeed(speed);
    updateSimulationStats();
}

void MainWindow::onVehiclesUpdated(const QVector<TrafficSimulator::Vehicle>& vehicles)
{
    mapVisualization->setVehicles(vehicles);
    updateSimulationStats();
}

void MainWindow::onTrafficLightsUpdated(const QVector<TrafficSimulator::TrafficLight>& lights)
{
    mapVisualization->setTrafficLights(lights);
    updateSimulationStats();
}

void MainWindow::onEdgeCongestionUpdated(qint64 from, qint64 to, const QString& status)
{
}

void MainWindow::updateSimulationStats()
{
    if (!trafficSimulator) return;

    int vehicleCount = trafficSimulator->getVehicleCount();
    int lightCount = trafficSimulator->getTrafficLightCount();
    double speed = 0.5 + (ui->speedSlider->value() / 10.0);

    ui->simStatsLabel->setText(QString("Vehicles: %1 | Lights: %2 | Speed: %3x")
                                   .arg(vehicleCount)
                                   .arg(lightCount)
                                   .arg(speed, 0, 'f', 1));
}

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
    // (Rest of dialog logic)
    directions += "</ol>";
    textEdit->setHtml(directions);
    layout->addWidget(textEdit);

    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeButton);

    dialog->exec();
    delete dialog;
}

void MainWindow::onPathSourceChanged(int index)
{
    if (index >= 0 && index < ui->simSourceCombo->count()) {
        ui->simSourceCombo->setCurrentIndex(index);
    }
}

void MainWindow::onPathDestChanged(int index)
{
    if (index >= 0 && index < ui->simDestCombo->count()) {
        ui->simDestCombo->setCurrentIndex(index);
    }
}

void MainWindow::on_actionBackToLogin_triggered()
{
    this->close();
    LoginDialog *login = new LoginDialog(dbManager, nullptr);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

void MainWindow::on_actionChat_triggered()
{
    IncidentFeedDialog *feedDialog = new IncidentFeedDialog(
        dbManager,
        m_currentUsername,
        m_currentUserEmail,
        this
        );
    feedDialog->setAttribute(Qt::WA_DeleteOnClose);
    feedDialog->show();
}

void MainWindow::onAddJamClicked()
{
    if (!trafficSimulator) return;

    qint64 from = ui->jamSourceCombo->currentData().toLongLong();
    qint64 to = ui->jamDestCombo->currentData().toLongLong();

    if (from <= 0 || to <= 0) {
        QMessageBox::warning(this, "Invalid Selection", "Please select valid source and destination nodes for the jam.");
        return;
    }
    if (from == to) {
        QMessageBox::warning(this, "Same Location", "Source and destination nodes for the jam cannot be the same.");
        return;
    }

    // Find the actual path between selected nodes (do not pass jams to this search)
    Graph::PathResult pathResult = graph.aStar(from, to, QSet<QPair<qint64,qint64>>());

    if (!pathResult.found) {
        QMessageBox::warning(this, "No Path", "No actual path exists between the selected nodes.");
        return;
    }

    // Build edges from the path and add them to the simulator
    QSet<QPair<qint64,qint64>> jamEdges;
    for (int i = 0; i < pathResult.path.size() - 1; ++i) {
        qint64 a = pathResult.path[i];
        qint64 b = pathResult.path[i+1];
        jamEdges.insert(qMakePair(a, b));        // block forward edge
        // Do NOT insert reverse here unless you intend to block both directions:
        jamEdges.insert(qMakePair(b, a));
    }

    // Add edges to simulator and update the map
    trafficSimulator->addManualJam(jamEdges);
    mapVisualization->setManualJams(trafficSimulator->getManualJams());
    mapVisualization->update();

    QMessageBox::information(this, "Jam Added",
                             QString("Manual traffic jam added along path between:\n%1\nand\n%2")
                                 .arg(ui->jamSourceCombo->currentText())
                                 .arg(ui->jamDestCombo->currentText()));
}

// --- NEWLY IMPLEMENTED SLOT ---
/**
 * @brief Slot for the "Reroute" button.
 * Finds an alternative path that avoids the currently displayed route.
 */
void MainWindow::onRerouteClicked()
{
    if (!m_currentPath.found || m_currentPath.path.size() < 2) {
        QMessageBox::warning(this, "No Path", "Please find a shortest path first before asking for a reroute.");
        return;
    }

    qint64 sourceId = ui->sourceCombo->currentData().toLongLong();
    qint64 destId = ui->destCombo->currentData().toLongLong();

    // If source/dest changed, just find a new shortest path
    if (sourceId != m_currentPath.path.first() || destId != m_currentPath.path.last()) {
        onFindPathClicked();
        return;
    }

    statusBar()->showMessage("Calculating alternative route...");

    // Block forward edges of current path only
    QSet<QPair<qint64, qint64>> blockedEdges;
    for (int i = 0; i < m_currentPath.path.size() - 1; ++i) {
        qint64 from = m_currentPath.path[i];
        qint64 to   = m_currentPath.path[i+1];
        if (graph.hasEdge(from, to)) blockedEdges.insert(qMakePair(from, to));
    }

    // Add manual jams if they exist in the graph
    if (trafficSimulator) {
        for (auto jam : trafficSimulator->getManualJams()) {
            if (graph.hasEdge(jam.first, jam.second)) {
                blockedEdges.insert(jam);
            }
        }
    }

    // --- Step 3: Find alternative path avoiding all blocked edges ---
    Graph::PathResult newResult = graph.aStar(sourceId, destId, blockedEdges);

    if (!newResult.found) {
        statusBar()->showMessage("No alternative route found");
        QMessageBox::warning(this, "No Alternative Path",
                             "Could not find an alternative route. Either the original path is the only option, or all alternatives are blocked.");
        return;
    }

    // --- Step 4: Display the new path ---
    mapVisualization->setShortestPath(newResult.path);
    displayRouteDetails(newResult);
    mapVisualization->focusOnPath(newResult.path);

    statusBar()->showMessage(QString("Alternative route found: %1 km, %2 stops")
                                 .arg(newResult.totalDistance, 0, 'f', 2)
                                 .arg(newResult.path.size()));

    // --- Step 5: Save the new path ---
    m_currentPath = newResult;
}
