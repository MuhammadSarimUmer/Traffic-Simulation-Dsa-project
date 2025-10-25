#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadMapClicked();
    void onFindPathClicked();

private:
    Ui::MainWindow *ui;
    Graph graph;
    bool mapLoaded;
};

#endif // MAINWINDOW_H
