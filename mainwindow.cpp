#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the Load Map button
    connect(ui->loadMapButton, &QPushButton::clicked, this, &MainWindow::onLoadMapClicked);

    // Set window title
    setWindowTitle("Traffic Control Simulator - Map & Graph Module");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadMapClicked()
{
    // Open file dialog to select .osm file
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select OpenStreetMap File",
        QDir::currentPath(),
        "OSM Files (*.osm);;All Files (*)"
        );

    if (filePath.isEmpty()) {
        return; // User cancelled
    }

    // Show loading message
    QMessageBox::information(this, "Loading", "Parsing map data, please wait...");

    // Load the map
    bool success = graph.loadFromOSM(filePath);

    if (success) {
        // Show success message with statistics
        QString message = QString(
                              "✅ Map loaded successfully!\n\n"
                              "Nodes: %1\n"
                              "Edges: %2"
                              ).arg(graph.getNodeCount()).arg(graph.getEdgeCount());

        QMessageBox::information(this, "Success", message);
    } else {
        QMessageBox::critical(this, "Error", "Failed to load map. Please check the file format.");
    }
}
