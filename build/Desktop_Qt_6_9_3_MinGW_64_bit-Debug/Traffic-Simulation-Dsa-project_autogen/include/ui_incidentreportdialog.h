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
    QFrame *line;
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
        IncidentReportDialog->resize(450, 350);
        IncidentReportDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background-color: #2b2b2b;\n"
"}\n"
"QLabel {\n"
"    color: #ffffff;\n"
"}\n"
"QLineEdit, QTextEdit {\n"
"    background-color: #3c3c3c;\n"
"    color: #ffffff;\n"
"    border: 1px solid #555;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
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
"QPushButton#cancelButton {\n"
"    background-color: #f44336;\n"
"}\n"
"QPushButton#cancelButton:hover {\n"
"    background-color: #da190b;\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentReportDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(IncidentReportDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        verticalLayout->addWidget(label);

        line = new QFrame(IncidentReportDialog);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(IncidentReportDialog);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        titleLineEdit = new QLineEdit(IncidentReportDialog);
        titleLineEdit->setObjectName("titleLineEdit");

        verticalLayout->addWidget(titleLineEdit);

        label_3 = new QLabel(IncidentReportDialog);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        descriptionTextEdit = new QTextEdit(IncidentReportDialog);
        descriptionTextEdit->setObjectName("descriptionTextEdit");

        verticalLayout->addWidget(descriptionTextEdit);

        label_4 = new QLabel(IncidentReportDialog);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        imagePathLineEdit = new QLineEdit(IncidentReportDialog);
        imagePathLineEdit->setObjectName("imagePathLineEdit");
        imagePathLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(imagePathLineEdit);

        browseButton = new QPushButton(IncidentReportDialog);
        browseButton->setObjectName("browseButton");

        horizontalLayout->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cancelButton = new QPushButton(IncidentReportDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout_2->addWidget(cancelButton);

        submitButton = new QPushButton(IncidentReportDialog);
        submitButton->setObjectName("submitButton");

        horizontalLayout_2->addWidget(submitButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(IncidentReportDialog);
        QObject::connect(cancelButton, &QPushButton::clicked, IncidentReportDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(IncidentReportDialog);
    } // setupUi

    void retranslateUi(QDialog *IncidentReportDialog)
    {
        IncidentReportDialog->setWindowTitle(QCoreApplication::translate("IncidentReportDialog", "Report New Incident", nullptr));
        label->setText(QCoreApplication::translate("IncidentReportDialog", "Create New Incident Report", nullptr));
        label_2->setText(QCoreApplication::translate("IncidentReportDialog", "Title:", nullptr));
        titleLineEdit->setPlaceholderText(QCoreApplication::translate("IncidentReportDialog", "e.g., Car Crash at Gulshan Chowrangi", nullptr));
        label_3->setText(QCoreApplication::translate("IncidentReportDialog", "Description:", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("IncidentReportDialog", "e.g., Heavy traffic, road is blocked. Please take an alternate route.", nullptr));
        label_4->setText(QCoreApplication::translate("IncidentReportDialog", "Image (Optional):", nullptr));
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
