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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadMapButton;
    QGroupBox *pathfindingGroup;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *sourceLabel;
    QComboBox *sourceCombo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *destLabel;
    QComboBox *destCombo;
    QPushButton *findPathButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        loadMapButton = new QPushButton(centralwidget);
        loadMapButton->setObjectName("loadMapButton");
        loadMapButton->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        loadMapButton->setFont(font);

        verticalLayout->addWidget(loadMapButton);

        pathfindingGroup = new QGroupBox(centralwidget);
        pathfindingGroup->setObjectName("pathfindingGroup");
        verticalLayout_2 = new QVBoxLayout(pathfindingGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        sourceLabel = new QLabel(pathfindingGroup);
        sourceLabel->setObjectName("sourceLabel");
        sourceLabel->setMinimumWidth(60);

        horizontalLayout->addWidget(sourceLabel);

        sourceCombo = new QComboBox(pathfindingGroup);
        sourceCombo->setObjectName("sourceCombo");
        sourceCombo->setMinimumHeight(35);

        horizontalLayout->addWidget(sourceCombo);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        destLabel = new QLabel(pathfindingGroup);
        destLabel->setObjectName("destLabel");
        destLabel->setMinimumWidth(60);

        horizontalLayout_2->addWidget(destLabel);

        destCombo = new QComboBox(pathfindingGroup);
        destCombo->setObjectName("destCombo");
        destCombo->setMinimumHeight(35);

        horizontalLayout_2->addWidget(destCombo);


        verticalLayout_2->addLayout(horizontalLayout_2);

        findPathButton = new QPushButton(pathfindingGroup);
        findPathButton->setObjectName("findPathButton");
        findPathButton->setMinimumSize(QSize(0, 45));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        findPathButton->setFont(font1);

        verticalLayout_2->addWidget(findPathButton);


        verticalLayout->addWidget(pathfindingGroup);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Traffic Control Simulator", nullptr));
        loadMapButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 Load Map", nullptr));
        pathfindingGroup->setTitle(QCoreApplication::translate("MainWindow", "Find Shortest Route (Dijkstra's Algorithm)", nullptr));
        sourceLabel->setText(QCoreApplication::translate("MainWindow", "From:", nullptr));
        destLabel->setText(QCoreApplication::translate("MainWindow", "To:", nullptr));
        findPathButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Find Shortest Path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
