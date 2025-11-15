/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
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
    QAction *actionBackToLogin;
    QAction *actionChat;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_Central;
    QScrollArea *mapScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *mapLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *controlDockWidget;
    QWidget *dockWidgetContents_LEFT;
    QVBoxLayout *verticalLayout_DOCK_LEFT;
    QScrollArea *controlScrollArea;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *areaLabel;
    QComboBox *areaSelectionCombo;
    QPushButton *loadMapButton;
    QFrame *separator1;
    QLabel *sourceLabel;
    QComboBox *sourceCombo;
    QLabel *destLabel;
    QComboBox *destCombo;
    QPushButton *findPathButton;
    QPushButton *clearPathButton;
    QFrame *separator2;
    QLabel *routeDetailsLabel;
    QTextEdit *routeDetailsText;
    QFrame *separator3;
    QLabel *zoomLabel;
    QHBoxLayout *zoomLayout;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *resetViewButton;
    QSpacerItem *verticalSpacer;
    QDockWidget *simulatorDockWidget;
    QWidget *dockWidgetContents_RIGHT;
    QVBoxLayout *verticalLayout_DOCK_RIGHT;
    QScrollArea *simulatorScrollArea;
    QWidget *simulatorDockContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *simulatorTitleLabel;
    QFrame *separator4;
    QLabel *simControlLabel;
    QHBoxLayout *simControlLayout;
    QPushButton *startSimButton;
    QPushButton *stopSimButton;
    QPushButton *resetSimButton;
    QFrame *separator5;
    QLabel *addVehicleLabel;
    QLabel *simSourceLabel;
    QComboBox *simSourceCombo;
    QLabel *simDestLabel;
    QComboBox *simDestCombo;
    QPushButton *addVehicleButton;
    QPushButton *addPriorityButton;
    QFrame *separator_jam;
    QLabel *jamLabel;
    QLabel *jamSourceLabel;
    QComboBox *jamSourceCombo;
    QLabel *jamDestLabel;
    QComboBox *jamDestCombo;
    QPushButton *addJamButton;
    QFrame *separator6;
    QLabel *speedLabel;
    QHBoxLayout *speedLayout;
    QLabel *speedMinLabel;
    QSlider *speedSlider;
    QLabel *speedMaxLabel;
    QFrame *separator7;
    QLabel *statsLabel;
    QLabel *simStatsLabel;
    QTextEdit *simInfoText;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        actionBackToLogin = new QAction(MainWindow);
        actionBackToLogin->setObjectName("actionBackToLogin");
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("go-previous");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionBackToLogin->setIcon(icon);
        actionChat = new QAction(MainWindow);
        actionChat->setObjectName("actionChat");
        QIcon icon1;
        iconThemeName = QString::fromUtf8("dialog-information");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionChat->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_Central = new QVBoxLayout(centralWidget);
        verticalLayout_Central->setSpacing(6);
        verticalLayout_Central->setContentsMargins(11, 11, 11, 11);
        verticalLayout_Central->setObjectName("verticalLayout_Central");
        verticalLayout_Central->setContentsMargins(0, 0, 0, 0);
        mapScrollArea = new QScrollArea(centralWidget);
        mapScrollArea->setObjectName("mapScrollArea");
        mapScrollArea->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: none;\n"
"    background-color: #1e1e1e;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #2b2b2b;\n"
"    width: 12px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #555555;\n"
"    min-height: 20px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #777777;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    border: none;\n"
"    background: #2b2b2b;\n"
"    height: 12px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: #555555;\n"
"    min-width: 20px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background: #777777;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"}"));
        mapScrollArea->setWidgetResizable(true);
        mapScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mapScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1198, 735));
        mapLayout = new QVBoxLayout(scrollAreaWidgetContents);
        mapLayout->setSpacing(0);
        mapLayout->setContentsMargins(11, 11, 11, 11);
        mapLayout->setObjectName("mapLayout");
        mapLayout->setContentsMargins(0, 0, 0, 0);
        mapScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_Central->addWidget(mapScrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1200, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        controlDockWidget = new QDockWidget(MainWindow);
        controlDockWidget->setObjectName("controlDockWidget");
        controlDockWidget->setMinimumSize(QSize(320, 608));
        dockWidgetContents_LEFT = new QWidget();
        dockWidgetContents_LEFT->setObjectName("dockWidgetContents_LEFT");
        verticalLayout_DOCK_LEFT = new QVBoxLayout(dockWidgetContents_LEFT);
        verticalLayout_DOCK_LEFT->setSpacing(6);
        verticalLayout_DOCK_LEFT->setContentsMargins(11, 11, 11, 11);
        verticalLayout_DOCK_LEFT->setObjectName("verticalLayout_DOCK_LEFT");
        verticalLayout_DOCK_LEFT->setContentsMargins(0, 0, 0, 0);
        controlScrollArea = new QScrollArea(dockWidgetContents_LEFT);
        controlScrollArea->setObjectName("controlScrollArea");
        controlScrollArea->setWidgetResizable(true);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dockWidgetContents->setGeometry(QRect(0, 0, 318, 697));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        areaLabel = new QLabel(dockWidgetContents);
        areaLabel->setObjectName("areaLabel");
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        areaLabel->setFont(font);

        verticalLayout->addWidget(areaLabel);

        areaSelectionCombo = new QComboBox(dockWidgetContents);
        areaSelectionCombo->setObjectName("areaSelectionCombo");

        verticalLayout->addWidget(areaSelectionCombo);

        loadMapButton = new QPushButton(dockWidgetContents);
        loadMapButton->setObjectName("loadMapButton");
        loadMapButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #45a049; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout->addWidget(loadMapButton);

        separator1 = new QFrame(dockWidgetContents);
        separator1->setObjectName("separator1");
        separator1->setFrameShape(QFrame::Shape::HLine);
        separator1->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(separator1);

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
        findPathButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #2196F3; color: white; padding: 8px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #0b7dda; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout->addWidget(findPathButton);

        clearPathButton = new QPushButton(dockWidgetContents);
        clearPathButton->setObjectName("clearPathButton");
        clearPathButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f44336; color: white; padding: 8px; border-radius: 4px; }\n"
"QPushButton:hover { background-color: #da190b; }"));

        verticalLayout->addWidget(clearPathButton);

        separator2 = new QFrame(dockWidgetContents);
        separator2->setObjectName("separator2");
        separator2->setFrameShape(QFrame::Shape::HLine);
        separator2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(separator2);

        routeDetailsLabel = new QLabel(dockWidgetContents);
        routeDetailsLabel->setObjectName("routeDetailsLabel");
        routeDetailsLabel->setFont(font);

        verticalLayout->addWidget(routeDetailsLabel);

        routeDetailsText = new QTextEdit(dockWidgetContents);
        routeDetailsText->setObjectName("routeDetailsText");
        routeDetailsText->setMinimumSize(QSize(0, 200));
        routeDetailsText->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
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
"}"));
        routeDetailsText->setReadOnly(true);

        verticalLayout->addWidget(routeDetailsText);

        separator3 = new QFrame(dockWidgetContents);
        separator3->setObjectName("separator3");
        separator3->setFrameShape(QFrame::Shape::HLine);
        separator3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(separator3);

        zoomLabel = new QLabel(dockWidgetContents);
        zoomLabel->setObjectName("zoomLabel");
        zoomLabel->setFont(font);

        verticalLayout->addWidget(zoomLabel);

        zoomLayout = new QHBoxLayout();
        zoomLayout->setSpacing(6);
        zoomLayout->setObjectName("zoomLayout");
        zoomInButton = new QPushButton(dockWidgetContents);
        zoomInButton->setObjectName("zoomInButton");
        zoomInButton->setStyleSheet(QString::fromUtf8("QPushButton { padding: 6px; }"));

        zoomLayout->addWidget(zoomInButton);

        zoomOutButton = new QPushButton(dockWidgetContents);
        zoomOutButton->setObjectName("zoomOutButton");
        zoomOutButton->setStyleSheet(QString::fromUtf8("QPushButton { padding: 6px; }"));

        zoomLayout->addWidget(zoomOutButton);


        verticalLayout->addLayout(zoomLayout);

        resetViewButton = new QPushButton(dockWidgetContents);
        resetViewButton->setObjectName("resetViewButton");
        resetViewButton->setStyleSheet(QString::fromUtf8("QPushButton { padding: 6px; }"));

        verticalLayout->addWidget(resetViewButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        controlScrollArea->setWidget(dockWidgetContents);

        verticalLayout_DOCK_LEFT->addWidget(controlScrollArea);

        controlDockWidget->setWidget(dockWidgetContents_LEFT);
        MainWindow->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, controlDockWidget);
        simulatorDockWidget = new QDockWidget(MainWindow);
        simulatorDockWidget->setObjectName("simulatorDockWidget");
        simulatorDockWidget->setMinimumSize(QSize(320, 608));
        dockWidgetContents_RIGHT = new QWidget();
        dockWidgetContents_RIGHT->setObjectName("dockWidgetContents_RIGHT");
        verticalLayout_DOCK_RIGHT = new QVBoxLayout(dockWidgetContents_RIGHT);
        verticalLayout_DOCK_RIGHT->setSpacing(6);
        verticalLayout_DOCK_RIGHT->setContentsMargins(11, 11, 11, 11);
        verticalLayout_DOCK_RIGHT->setObjectName("verticalLayout_DOCK_RIGHT");
        verticalLayout_DOCK_RIGHT->setContentsMargins(0, 0, 0, 0);
        simulatorScrollArea = new QScrollArea(dockWidgetContents_RIGHT);
        simulatorScrollArea->setObjectName("simulatorScrollArea");
        simulatorScrollArea->setWidgetResizable(true);
        simulatorDockContents = new QWidget();
        simulatorDockContents->setObjectName("simulatorDockContents");
        simulatorDockContents->setGeometry(QRect(0, 0, 318, 950));
        verticalLayout_2 = new QVBoxLayout(simulatorDockContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        simulatorTitleLabel = new QLabel(simulatorDockContents);
        simulatorTitleLabel->setObjectName("simulatorTitleLabel");
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        simulatorTitleLabel->setFont(font1);
        simulatorTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(simulatorTitleLabel);

        separator4 = new QFrame(simulatorDockContents);
        separator4->setObjectName("separator4");
        separator4->setFrameShape(QFrame::Shape::HLine);
        separator4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(separator4);

        simControlLabel = new QLabel(simulatorDockContents);
        simControlLabel->setObjectName("simControlLabel");
        simControlLabel->setFont(font);

        verticalLayout_2->addWidget(simControlLabel);

        simControlLayout = new QHBoxLayout();
        simControlLayout->setSpacing(6);
        simControlLayout->setObjectName("simControlLayout");
        startSimButton = new QPushButton(simulatorDockContents);
        startSimButton->setObjectName("startSimButton");
        startSimButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #4CAF50; color: white; padding: 10px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #45a049; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        simControlLayout->addWidget(startSimButton);

        stopSimButton = new QPushButton(simulatorDockContents);
        stopSimButton->setObjectName("stopSimButton");
        stopSimButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #ff9800; color: white; padding: 10px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #e68900; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        simControlLayout->addWidget(stopSimButton);


        verticalLayout_2->addLayout(simControlLayout);

        resetSimButton = new QPushButton(simulatorDockContents);
        resetSimButton->setObjectName("resetSimButton");
        resetSimButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f44336; color: white; padding: 8px; border-radius: 4px; }\n"
"QPushButton:hover { background-color: #da190b; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout_2->addWidget(resetSimButton);

        separator5 = new QFrame(simulatorDockContents);
        separator5->setObjectName("separator5");
        separator5->setFrameShape(QFrame::Shape::HLine);
        separator5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(separator5);

        addVehicleLabel = new QLabel(simulatorDockContents);
        addVehicleLabel->setObjectName("addVehicleLabel");
        addVehicleLabel->setFont(font);

        verticalLayout_2->addWidget(addVehicleLabel);

        simSourceLabel = new QLabel(simulatorDockContents);
        simSourceLabel->setObjectName("simSourceLabel");

        verticalLayout_2->addWidget(simSourceLabel);

        simSourceCombo = new QComboBox(simulatorDockContents);
        simSourceCombo->setObjectName("simSourceCombo");

        verticalLayout_2->addWidget(simSourceCombo);

        simDestLabel = new QLabel(simulatorDockContents);
        simDestLabel->setObjectName("simDestLabel");

        verticalLayout_2->addWidget(simDestLabel);

        simDestCombo = new QComboBox(simulatorDockContents);
        simDestCombo->setObjectName("simDestCombo");

        verticalLayout_2->addWidget(simDestCombo);

        addVehicleButton = new QPushButton(simulatorDockContents);
        addVehicleButton->setObjectName("addVehicleButton");
        addVehicleButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #2196F3; color: white; padding: 10px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #0b7dda; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout_2->addWidget(addVehicleButton);

        addPriorityButton = new QPushButton(simulatorDockContents);
        addPriorityButton->setObjectName("addPriorityButton");
        addPriorityButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #e91e63; color: white; padding: 10px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #c2185b; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout_2->addWidget(addPriorityButton);

        separator_jam = new QFrame(simulatorDockContents);
        separator_jam->setObjectName("separator_jam");
        separator_jam->setFrameShape(QFrame::Shape::HLine);
        separator_jam->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(separator_jam);

        jamLabel = new QLabel(simulatorDockContents);
        jamLabel->setObjectName("jamLabel");
        jamLabel->setFont(font);

        verticalLayout_2->addWidget(jamLabel);

        jamSourceLabel = new QLabel(simulatorDockContents);
        jamSourceLabel->setObjectName("jamSourceLabel");

        verticalLayout_2->addWidget(jamSourceLabel);

        jamSourceCombo = new QComboBox(simulatorDockContents);
        jamSourceCombo->setObjectName("jamSourceCombo");

        verticalLayout_2->addWidget(jamSourceCombo);

        jamDestLabel = new QLabel(simulatorDockContents);
        jamDestLabel->setObjectName("jamDestLabel");

        verticalLayout_2->addWidget(jamDestLabel);

        jamDestCombo = new QComboBox(simulatorDockContents);
        jamDestCombo->setObjectName("jamDestCombo");

        verticalLayout_2->addWidget(jamDestCombo);

        addJamButton = new QPushButton(simulatorDockContents);
        addJamButton->setObjectName("addJamButton");
        addJamButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f44336; color: white; padding: 10px; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #da190b; }\n"
"QPushButton:disabled { background-color: #cccccc; }"));

        verticalLayout_2->addWidget(addJamButton);

        separator6 = new QFrame(simulatorDockContents);
        separator6->setObjectName("separator6");
        separator6->setFrameShape(QFrame::Shape::HLine);
        separator6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(separator6);

        speedLabel = new QLabel(simulatorDockContents);
        speedLabel->setObjectName("speedLabel");
        speedLabel->setFont(font);

        verticalLayout_2->addWidget(speedLabel);

        speedLayout = new QHBoxLayout();
        speedLayout->setSpacing(6);
        speedLayout->setObjectName("speedLayout");
        speedMinLabel = new QLabel(simulatorDockContents);
        speedMinLabel->setObjectName("speedMinLabel");

        speedLayout->addWidget(speedMinLabel);

        speedSlider = new QSlider(simulatorDockContents);
        speedSlider->setObjectName("speedSlider");
        speedSlider->setMinimum(0);
        speedSlider->setMaximum(20);
        speedSlider->setValue(10);
        speedSlider->setOrientation(Qt::Horizontal);

        speedLayout->addWidget(speedSlider);

        speedMaxLabel = new QLabel(simulatorDockContents);
        speedMaxLabel->setObjectName("speedMaxLabel");

        speedLayout->addWidget(speedMaxLabel);


        verticalLayout_2->addLayout(speedLayout);

        separator7 = new QFrame(simulatorDockContents);
        separator7->setObjectName("separator7");
        separator7->setFrameShape(QFrame::Shape::HLine);
        separator7->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(separator7);

        statsLabel = new QLabel(simulatorDockContents);
        statsLabel->setObjectName("statsLabel");
        statsLabel->setFont(font);

        verticalLayout_2->addWidget(statsLabel);

        simStatsLabel = new QLabel(simulatorDockContents);
        simStatsLabel->setObjectName("simStatsLabel");
        simStatsLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #2b2b2b;\n"
"    color: #ffffff;\n"
"    border: 1px solid #444;\n"
"    border-radius: 5px;\n"
"    padding: 15px;\n"
"    font-family: 'Courier New', monospace;\n"
"    font-size: 10pt;\n"
"}"));
        simStatsLabel->setAlignment(Qt::AlignCenter);
        simStatsLabel->setWordWrap(true);

        verticalLayout_2->addWidget(simStatsLabel);

        simInfoText = new QTextEdit(simulatorDockContents);
        simInfoText->setObjectName("simInfoText");
        simInfoText->setMinimumSize(QSize(0, 150));
        simInfoText->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #2b2b2b;\n"
"    color: #aaaaaa;\n"
"    border: 1px solid #444;\n"
"    border-radius: 5px;\n"
"    padding: 10px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 9pt;\n"
"}"));
        simInfoText->setReadOnly(true);

        verticalLayout_2->addWidget(simInfoText);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        simulatorScrollArea->setWidget(simulatorDockContents);

        verticalLayout_DOCK_RIGHT->addWidget(simulatorScrollArea);

        simulatorDockWidget->setWidget(dockWidgetContents_RIGHT);
        MainWindow->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, simulatorDockWidget);

        mainToolBar->addAction(actionBackToLogin);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionChat);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Traffic Control Simulator - Karachi", nullptr));
        actionBackToLogin->setText(QCoreApplication::translate("MainWindow", "Back to Login", nullptr));
#if QT_CONFIG(tooltip)
        actionBackToLogin->setToolTip(QCoreApplication::translate("MainWindow", "Log out and return to the login screen", nullptr));
#endif // QT_CONFIG(tooltip)
        actionChat->setText(QCoreApplication::translate("MainWindow", "Chat", nullptr));
#if QT_CONFIG(tooltip)
        actionChat->setToolTip(QCoreApplication::translate("MainWindow", "Open Chat", nullptr));
#endif // QT_CONFIG(tooltip)
        controlDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Map & Pathfinding", nullptr));
        areaLabel->setText(QCoreApplication::translate("MainWindow", "1. Select Area:", nullptr));
        loadMapButton->setText(QCoreApplication::translate("MainWindow", "Load Map Area", nullptr));
        sourceLabel->setText(QCoreApplication::translate("MainWindow", "2. Select Source:", nullptr));
        destLabel->setText(QCoreApplication::translate("MainWindow", "3. Select Destination:", nullptr));
        findPathButton->setText(QCoreApplication::translate("MainWindow", "Find Shortest Path", nullptr));
        clearPathButton->setText(QCoreApplication::translate("MainWindow", "Clear Path", nullptr));
        routeDetailsLabel->setText(QCoreApplication::translate("MainWindow", "Route Details:", nullptr));
        zoomLabel->setText(QCoreApplication::translate("MainWindow", "Map Zoom:", nullptr));
        zoomInButton->setText(QCoreApplication::translate("MainWindow", "Zoom In (+)", nullptr));
        zoomOutButton->setText(QCoreApplication::translate("MainWindow", "Zoom Out (-)", nullptr));
        resetViewButton->setText(QCoreApplication::translate("MainWindow", "Reset View", nullptr));
        simulatorDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Traffic Simulator", nullptr));
        simulatorTitleLabel->setText(QCoreApplication::translate("MainWindow", "Traffic Simulation Control", nullptr));
        simControlLabel->setText(QCoreApplication::translate("MainWindow", "Simulation Control:", nullptr));
        startSimButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopSimButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        resetSimButton->setText(QCoreApplication::translate("MainWindow", "Reset Simulation", nullptr));
        addVehicleLabel->setText(QCoreApplication::translate("MainWindow", "Add Vehicles:", nullptr));
        simSourceLabel->setText(QCoreApplication::translate("MainWindow", "From:", nullptr));
        simDestLabel->setText(QCoreApplication::translate("MainWindow", "To:", nullptr));
        addVehicleButton->setText(QCoreApplication::translate("MainWindow", "Add Regular Vehicle", nullptr));
        addPriorityButton->setText(QCoreApplication::translate("MainWindow", "Add Priority Vehicle (Ambulance)", nullptr));
        jamLabel->setText(QCoreApplication::translate("MainWindow", "Add Manual Jam:", nullptr));
        jamSourceLabel->setText(QCoreApplication::translate("MainWindow", "From:", nullptr));
        jamDestLabel->setText(QCoreApplication::translate("MainWindow", "To:", nullptr));
        addJamButton->setText(QCoreApplication::translate("MainWindow", "Add Jam", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "Simulation Speed:", nullptr));
        speedMinLabel->setText(QCoreApplication::translate("MainWindow", "0.5x", nullptr));
        speedMaxLabel->setText(QCoreApplication::translate("MainWindow", "2.5x", nullptr));
        statsLabel->setText(QCoreApplication::translate("MainWindow", "Statistics:", nullptr));
        simStatsLabel->setText(QCoreApplication::translate("MainWindow", "Vehicles: 0 | Lights: 0 | Speed: 1.0x", nullptr));
        simInfoText->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body>\n"
"<p><span style=\" font-weight:600;\">How to use:</span></p>\n"
"<ol style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Load a map area first</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Click 'Start' to begin simulation</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Add vehicles between locations</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">W"
                        "atch traffic flow in real-time</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Red vehicles = Priority (ambulances)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Green/Red circles = Traffic lights</li></ol>\n"
"</body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
