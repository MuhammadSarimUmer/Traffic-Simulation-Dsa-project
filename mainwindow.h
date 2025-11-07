#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "graph.h"
#include "map_loader.h" // Include the new loader

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// --- Added Struct for Area Bounds ---
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
    void onLoadMapAreaClicked();              // ✅ Added missing slot
    void onFindPathClicked();                 // ✅ Already used
    void onMapDataLoaded(const QByteArray& data);
    void onMapLoadFailed(const QString& error);

private:
    void setupAreaSelection();                // ✅ Added missing helper
    void populateComboBoxes();                // ✅ Already exists

    Ui::MainWindow *ui;
    Graph graph;
    MapLoader *mapLoader;
    bool mapLoaded;

    QMap<QString, BoundingBox> areaBounds;    // ✅ Added for district boundaries
};

#endif // MAINWINDOW_H
