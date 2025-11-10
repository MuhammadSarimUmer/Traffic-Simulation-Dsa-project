/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *controlDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *areaLabel;
    QComboBox *areaSelectionCombo;
    QPushButton *loadMapButton;
    QSpacerItem *verticalSpacer_1;
    QLabel *sourceLabel;
    QComboBox *sourceCombo;
    QLabel *destLabel;
    QComboBox *destCombo;
    QPushButton *findPathButton;
    QPushButton *clearPathButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *routeDetailsLabel;
    QTextEdit *routeDetailsText;
    QSpacerItem *verticalSpacer_3;
    QLabel *zoomLabel;
    QHBoxLayout *zoomLayout;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *resetViewButton;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        controlDockWidget = new QDockWidget(MainWindow);
        controlDockWidget->setObjectName("controlDockWidget");
        controlDockWidget->setMinimumSize(QSize(300, 200));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        areaLabel = new QLabel(dockWidgetContents);
        areaLabel->setObjectName("areaLabel");
        QFont font;
        font.setBold(true);
        areaLabel->setFont(font);

        verticalLayout->addWidget(areaLabel);

        areaSelectionCombo = new QComboBox(dockWidgetContents);
        areaSelectionCombo->setObjectName("areaSelectionCombo");

        verticalLayout->addWidget(areaSelectionCombo);

        loadMapButton = new QPushButton(dockWidgetContents);
        loadMapButton->setObjectName("loadMapButton");

        verticalLayout->addWidget(loadMapButton);

        verticalSpacer_1 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        sourceLabel = new QLabel(dockWidgetContents);
        sourceLabel->setObjectName("sourceLabel");
        sourceLabel->setFont(font);

        verticalLayout->addWidget(sourceLabel);

        sourceCombo = new QComboBox(dockWidgetContents);
        sourceCombo->setObjectName("sourceCombo");

        verticalLayout->addWidget(sourceCombo);

        destLabel = new QLabel(dockWidgetContents);
        destLabel->setObjectName("destLabel");
        destLabel->setFont(font);

        verticalLayout->addWidget(destLabel);

        destCombo = new QComboBox(dockWidgetContents);
        destCombo->setObjectName("destCombo");

        verticalLayout->addWidget(destCombo);

        findPathButton = new QPushButton(dockWidgetContents);
        findPathButton->setObjectName("findPathButton");

        verticalLayout->addWidget(findPathButton);

        clearPathButton = new QPushButton(dockWidgetContents);
        clearPathButton->setObjectName("clearPathButton");

        verticalLayout->addWidget(clearPathButton);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        routeDetailsLabel = new QLabel(dockWidgetContents);
        routeDetailsLabel->setObjectName("routeDetailsLabel");
        routeDetailsLabel->setFont(font);

        verticalLayout->addWidget(routeDetailsLabel);

        routeDetailsText = new QTextEdit(dockWidgetContents);
        routeDetailsText->setObjectName("routeDetailsText");
        routeDetailsText->setMinimumSize(QSize(0, 250));
        routeDetailsText->setMaximumSize(QSize(16777215, 16777215));
        routeDetailsText->setReadOnly(true);

        verticalLayout->addWidget(routeDetailsText);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        zoomLabel = new QLabel(dockWidgetContents);
        zoomLabel->setObjectName("zoomLabel");
        zoomLabel->setFont(font);

        verticalLayout->addWidget(zoomLabel);

        zoomLayout = new QHBoxLayout();
        zoomLayout->setSpacing(6);
        zoomLayout->setObjectName("zoomLayout");
        zoomInButton = new QPushButton(dockWidgetContents);
        zoomInButton->setObjectName("zoomInButton");

        zoomLayout->addWidget(zoomInButton);

        zoomOutButton = new QPushButton(dockWidgetContents);
        zoomOutButton->setObjectName("zoomOutButton");

        zoomLayout->addWidget(zoomOutButton);


        verticalLayout->addLayout(zoomLayout);

        resetViewButton = new QPushButton(dockWidgetContents);
        resetViewButton->setObjectName("resetViewButton");

        verticalLayout->addWidget(resetViewButton);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        controlDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, controlDockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Traffic Control Simulator - Karachi", nullptr));
        controlDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Map Controls", nullptr));
        areaLabel->setText(QCoreApplication::translate("MainWindow", "1. Select Area:", nullptr));
        loadMapButton->setText(QCoreApplication::translate("MainWindow", "Load Map Area", nullptr));
        loadMapButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }\n"
"QPushButton:hover { background-color: #45a049; }\n"
"QPushButton:disabled { background-color: #cccccc; }", nullptr));
        sourceLabel->setText(QCoreApplication::translate("MainWindow", "2. Select Source:", nullptr));
        destLabel->setText(QCoreApplication::translate("MainWindow", "3. Select Destination:", nullptr));
        findPathButton->setText(QCoreApplication::translate("MainWindow", "Find Shortest Path", nullptr));
        findPathButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #2196F3; color: white; padding: 8px; border-radius: 4px; }\n"
"QPushButton:hover { background-color: #0b7dda; }\n"
"QPushButton:disabled { background-color: #cccccc; }", nullptr));
        clearPathButton->setText(QCoreApplication::translate("MainWindow", "Clear Path", nullptr));
        clearPathButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #f44336; color: white; padding: 8px; border-radius: 4px; }\n"
"QPushButton:hover { background-color: #da190b; }", nullptr));
        routeDetailsLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 Route Details:", nullptr));
        routeDetailsText->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; color:#888888;\">Route details will appear here</span></p></body></html>", nullptr));
        routeDetailsText->setStyleSheet(QCoreApplication::translate("MainWindow", "QTextEdit {\n"
"    background-color: #2b2b2b;\n"
"    color: #ffffff;\n"
"    border: 1px solid #444;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 10pt;\n"
"}\n"
"QTextEdit:focus {\n"
"    border: 1px solid #2196F3;\n"
"}", nullptr));
        zoomLabel->setText(QCoreApplication::translate("MainWindow", "Map Zoom:", nullptr));
        zoomInButton->setText(QCoreApplication::translate("MainWindow", "Zoom In (+)", nullptr));
        zoomInButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { padding: 6px; }", nullptr));
        zoomOutButton->setText(QCoreApplication::translate("MainWindow", "Zoom Out (-)", nullptr));
        zoomOutButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { padding: 6px; }", nullptr));
        resetViewButton->setText(QCoreApplication::translate("MainWindow", "Reset View", nullptr));
        resetViewButton->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { padding: 6px; }", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
