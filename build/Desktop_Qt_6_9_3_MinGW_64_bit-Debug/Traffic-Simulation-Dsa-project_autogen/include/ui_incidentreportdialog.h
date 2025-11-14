/********************************************************************************
** Form generated from reading UI file 'incidentreportdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCIDENTREPORTDIALOG_H
#define UI_INCIDENTREPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IncidentReportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *subtitleLabel;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QLineEdit *titleLineEdit;
    QLabel *label_3;
    QTextEdit *descriptionTextEdit;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *imagePathLineEdit;
    QPushButton *browseButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelButton;
    QPushButton *submitButton;

    void setupUi(QDialog *IncidentReportDialog)
    {
        if (IncidentReportDialog->objectName().isEmpty())
            IncidentReportDialog->setObjectName("IncidentReportDialog");
        IncidentReportDialog->resize(450, 520);
        IncidentReportDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #1e1e1e, stop:1 #2b2b2b);\n"
"}\n"
"QLabel {\n"
"    color: #e8e8e8;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"QLineEdit, QTextEdit {\n"
"    background-color: rgba(255, 255, 255, 0.08);\n"
"    color: #ffffff;\n"
"    border: 2px solid rgba(255, 255, 255, 0.1);\n"
"    border-radius: 6px;\n"
"    padding: 8px 12px;\n"
"    font-size: 12px;\n"
"    selection-background-color: #2196F3;\n"
"}\n"
"QLineEdit:focus, QTextEdit:focus {\n"
"    border: 2px solid #2196F3;\n"
"    background-color: rgba(255, 255, 255, 0.12);\n"
"}\n"
"QLineEdit:hover, QTextEdit:hover {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"}\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #2196F3, stop:1 #0b7dda);\n"
"    color: white;\n"
"    padding: 10px 20px;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    font-weight: "
                        "600;\n"
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
"QPushButton#cancelButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #f44336, stop:1 #da190b);\n"
"}\n"
"QPushButton#cancelButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                stop:0 #da190b, stop:1 #c41606);\n"
"}\n"
"QPushButton#browseButton {\n"
"    background: rgba(255, 255, 255, 0.1);\n"
"    border: 2px solid rgba(255, 255, 255, 0.2);\n"
"}\n"
"QPushButton#browseButton:hover {\n"
"    background: rgba(255, 255, 255, 0.15);\n"
"    border: 2px solid rgba(255, 255, 255, 0.3);\n"
"}\n"
""
                        "QTextEdit {\n"
"    padding: 10px;\n"
"}\n"
"Line {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentReportDialog);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(25, 25, 25, 25);
        label = new QLabel(IncidentReportDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: #2196F3;\n"
"padding-bottom: 4px;"));

        verticalLayout->addWidget(label);

        subtitleLabel = new QLabel(IncidentReportDialog);
        subtitleLabel->setObjectName("subtitleLabel");
        QFont font1;
        font1.setPointSize(8);
        subtitleLabel->setFont(font1);
        subtitleLabel->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.6);\n"
"margin-bottom: 6px;"));

        verticalLayout->addWidget(subtitleLabel);

        line = new QFrame(IncidentReportDialog);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0.15);\n"
"height: 1px;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_2 = new QLabel(IncidentReportDialog);
        label_2->setObjectName("label_2");
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.8);\n"
"font-weight: 500;\n"
"margin-bottom: 3px;"));

        verticalLayout->addWidget(label_2);

        titleLineEdit = new QLineEdit(IncidentReportDialog);
        titleLineEdit->setObjectName("titleLineEdit");

        verticalLayout->addWidget(titleLineEdit);

        label_3 = new QLabel(IncidentReportDialog);
        label_3->setObjectName("label_3");
        QFont font3;
        font3.setPointSize(9);
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.8);\n"
"font-weight: 500;\n"
"margin-top: 6px;\n"
"margin-bottom: 3px;"));

        verticalLayout->addWidget(label_3);

        descriptionTextEdit = new QTextEdit(IncidentReportDialog);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setMinimumSize(QSize(0, 80));

        verticalLayout->addWidget(descriptionTextEdit);

        label_4 = new QLabel(IncidentReportDialog);
        label_4->setObjectName("label_4");
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.8);\n"
"font-weight: 500;\n"
"margin-top: 6px;\n"
"margin-bottom: 3px;"));

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        imagePathLineEdit = new QLineEdit(IncidentReportDialog);
        imagePathLineEdit->setObjectName("imagePathLineEdit");
        imagePathLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(imagePathLineEdit);

        browseButton = new QPushButton(IncidentReportDialog);
        browseButton->setObjectName("browseButton");
        browseButton->setMinimumSize(QSize(90, 0));

        horizontalLayout->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cancelButton = new QPushButton(IncidentReportDialog);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(cancelButton);

        submitButton = new QPushButton(IncidentReportDialog);
        submitButton->setObjectName("submitButton");
        submitButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(submitButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(IncidentReportDialog);
        QObject::connect(cancelButton, &QPushButton::clicked, IncidentReportDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(IncidentReportDialog);
    } // setupUi

    void retranslateUi(QDialog *IncidentReportDialog)
    {
        IncidentReportDialog->setWindowTitle(QCoreApplication::translate("IncidentReportDialog", "Report New Incident", nullptr));
        label->setText(QCoreApplication::translate("IncidentReportDialog", "Create Incident Report", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("IncidentReportDialog", "Help your community stay informed", nullptr));
        label_2->setText(QCoreApplication::translate("IncidentReportDialog", "Title", nullptr));
        titleLineEdit->setPlaceholderText(QCoreApplication::translate("IncidentReportDialog", "e.g., Car Crash at Gulshan Chowrangi", nullptr));
        label_3->setText(QCoreApplication::translate("IncidentReportDialog", "Description", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("IncidentReportDialog", "Provide details about the incident, location, and important information...", nullptr));
        label_4->setText(QCoreApplication::translate("IncidentReportDialog", "Image (Optional)", nullptr));
        imagePathLineEdit->setPlaceholderText(QCoreApplication::translate("IncidentReportDialog", "No image selected...", nullptr));
        browseButton->setText(QCoreApplication::translate("IncidentReportDialog", "Browse...", nullptr));
        cancelButton->setText(QCoreApplication::translate("IncidentReportDialog", "Cancel", nullptr));
        submitButton->setText(QCoreApplication::translate("IncidentReportDialog", "Submit Report", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncidentReportDialog: public Ui_IncidentReportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCIDENTREPORTDIALOG_H
