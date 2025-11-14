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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IncidentFeedDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *headerLayout;
    QLabel *label;
    QLabel *subtitleLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *feedLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QPushButton *reportIncidentButton;

    void setupUi(QDialog *IncidentFeedDialog)
    {
        if (IncidentFeedDialog->objectName().isEmpty())
            IncidentFeedDialog->setObjectName("IncidentFeedDialog");
        IncidentFeedDialog->resize(500, 600);
        IncidentFeedDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #1e1e1e, stop:1 #2b2b2b);\n"
"}\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #2196F3, stop:1 #0b7dda);\n"
"    color: white;\n"
"    padding: 10px 16px;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    font-weight: 600;\n"
"    font-size: 12px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #0b7dda, stop:1 #0961a5);\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #0961a5, stop:1 #074d87);\n"
"}\n"
"QPushButton#refreshButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #4CAF50, stop:1 #45a049);\n"
"}\n"
"QPushButton#refreshButton:hover {"
                        "\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #45a049, stop:1 #3d8b40);\n"
"}\n"
"QScrollArea {\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
"QScrollBar:vertical {\n"
"    background: rgba(255, 255, 255, 0.05);\n"
"    width: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"    background: rgba(255, 255, 255, 0.2);\n"
"    border-radius: 5px;\n"
"    min-height: 30px;\n"
"}\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: rgba(255, 255, 255, 0.3);\n"
"}\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"QLabel {\n"
"    color: #ffffff;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentFeedDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        headerLayout = new QVBoxLayout();
        headerLayout->setSpacing(6);
        headerLayout->setObjectName("headerLayout");
        label = new QLabel(IncidentFeedDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: #2196F3;"));

        headerLayout->addWidget(label);

        subtitleLabel = new QLabel(IncidentFeedDialog);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setPointSize(8);
        subtitleLabel->setFont(font1);
        subtitleLabel->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.6);"));

        headerLayout->addWidget(subtitleLabel);


        verticalLayout->addLayout(headerLayout);

        scrollArea = new QScrollArea(IncidentFeedDialog);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    background-color: transparent;\n"
"}\n"
"QWidget#scrollAreaWidgetContents {\n"
"    background-color: transparent;\n"
"}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 450, 450));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("#scrollAreaWidgetContents {\n"
"    background-color: transparent;\n"
"}"));
        feedLayout = new QVBoxLayout(scrollAreaWidgetContents);
        feedLayout->setSpacing(12);
        feedLayout->setObjectName("feedLayout");
        feedLayout->setContentsMargins(0, 0, 5, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        refreshButton = new QPushButton(IncidentFeedDialog);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(refreshButton);

        reportIncidentButton = new QPushButton(IncidentFeedDialog);
        reportIncidentButton->setObjectName("reportIncidentButton");
        reportIncidentButton->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(reportIncidentButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(IncidentFeedDialog);

        QMetaObject::connectSlotsByName(IncidentFeedDialog);
    } // setupUi

    void retranslateUi(QDialog *IncidentFeedDialog)
    {
        IncidentFeedDialog->setWindowTitle(QCoreApplication::translate("IncidentFeedDialog", "Live Incident Feed", nullptr));
        label->setText(QCoreApplication::translate("IncidentFeedDialog", "Live Community Feed", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("IncidentFeedDialog", "Stay updated with real-time incident reports", nullptr));
        refreshButton->setText(QCoreApplication::translate("IncidentFeedDialog", "\360\237\224\204  Refresh", nullptr));
        reportIncidentButton->setText(QCoreApplication::translate("IncidentFeedDialog", "\360\237\223\235  Report Incident", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncidentFeedDialog: public Ui_IncidentFeedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCIDENTFEEDDIALOG_H
