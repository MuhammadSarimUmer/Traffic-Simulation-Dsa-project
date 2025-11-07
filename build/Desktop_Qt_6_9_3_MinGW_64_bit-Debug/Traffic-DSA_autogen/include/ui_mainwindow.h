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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *areaLayout;
    QLabel *areaLabel;
    QComboBox *areaSelectionCombo;
    QPushButton *loadMapButton;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *sourceCombo;
    QLabel *label_2;
    QComboBox *destCombo;
    QPushButton *findPathButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        areaLayout = new QHBoxLayout();
        areaLayout->setObjectName("areaLayout");
        areaLabel = new QLabel(centralwidget);
        areaLabel->setObjectName("areaLabel");

        areaLayout->addWidget(areaLabel);

        areaSelectionCombo = new QComboBox(centralwidget);
        areaSelectionCombo->setObjectName("areaSelectionCombo");

        areaLayout->addWidget(areaSelectionCombo);


        verticalLayout->addLayout(areaLayout);

        loadMapButton = new QPushButton(centralwidget);
        loadMapButton->setObjectName("loadMapButton");

        verticalLayout->addWidget(loadMapButton);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        sourceCombo = new QComboBox(centralwidget);
        sourceCombo->setObjectName("sourceCombo");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, sourceCombo);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        destCombo = new QComboBox(centralwidget);
        destCombo->setObjectName("destCombo");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, destCombo);


        verticalLayout->addLayout(formLayout);

        findPathButton = new QPushButton(centralwidget);
        findPathButton->setObjectName("findPathButton");

        verticalLayout->addWidget(findPathButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 21));
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
        areaLabel->setText(QCoreApplication::translate("MainWindow", "Select Area:", nullptr));
        loadMapButton->setText(QCoreApplication::translate("MainWindow", "Load Map", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Source:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Destination:", nullptr));
        findPathButton->setText(QCoreApplication::translate("MainWindow", "Find Shortest Path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
