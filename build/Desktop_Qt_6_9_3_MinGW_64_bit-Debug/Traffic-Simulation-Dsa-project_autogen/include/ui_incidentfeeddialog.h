/********************************************************************************
** Form generated from reading UI file 'incidentfeeddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCIDENTFEEDDIALOG_H
#define UI_INCIDENTFEEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IncidentFeedDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *feedLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *reportIncidentButton;

    void setupUi(QDialog *IncidentFeedDialog)
    {
        if (IncidentFeedDialog->objectName().isEmpty())
            IncidentFeedDialog->setObjectName("IncidentFeedDialog");
        IncidentFeedDialog->resize(500, 600);
        IncidentFeedDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background-color: #1e1e1e;\n"
"}\n"
"QPushButton {\n"
"    background-color: #2196F3;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0b7dda;\n"
"}\n"
"QPushButton#refreshButton {\n"
"    background-color: #4CAF50;\n"
"}\n"
"QPushButton#refreshButton:hover {\n"
"    background-color: #45a049;\n"
"}\n"
"QScrollArea {\n"
"    border: none;\n"
"}\n"
"QLabel {\n"
"        color: #ffffff;\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentFeedDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(IncidentFeedDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: #ffffff;"));

        verticalLayout->addWidget(label);

        scrollArea = new QScrollArea(IncidentFeedDialog);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 482, 497));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("#scrollAreaWidgetContents {\n"
"    background-color: #1e1e1e;\n"
"}"));
        feedLayout = new QVBoxLayout(scrollAreaWidgetContents);
        feedLayout->setObjectName("feedLayout");
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        refreshButton = new QPushButton(IncidentFeedDialog);
        refreshButton->setObjectName("refreshButton");

        horizontalLayout->addWidget(refreshButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        reportIncidentButton = new QPushButton(IncidentFeedDialog);
        reportIncidentButton->setObjectName("reportIncidentButton");

        horizontalLayout->addWidget(reportIncidentButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(IncidentFeedDialog);

        QMetaObject::connectSlotsByName(IncidentFeedDialog);
    } // setupUi

    void retranslateUi(QDialog *IncidentFeedDialog)
    {
        IncidentFeedDialog->setWindowTitle(QCoreApplication::translate("IncidentFeedDialog", "Live Incident Feed", nullptr));
        label->setText(QCoreApplication::translate("IncidentFeedDialog", "Live Community Incident Feed", nullptr));
        refreshButton->setText(QCoreApplication::translate("IncidentFeedDialog", "Refresh Feed", nullptr));
        reportIncidentButton->setText(QCoreApplication::translate("IncidentFeedDialog", "Report New Incident", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncidentFeedDialog: public Ui_IncidentFeedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCIDENTFEEDDIALOG_H
