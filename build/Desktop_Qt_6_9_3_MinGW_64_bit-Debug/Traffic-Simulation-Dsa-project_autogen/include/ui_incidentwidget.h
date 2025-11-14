/********************************************************************************
** Form generated from reading UI file 'incidentwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCIDENTWIDGET_H
#define UI_INCIDENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IncidentWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *userInfoLabel;
    QLabel *timestampLabel;
    QFrame *line;
    QLabel *descriptionLabel;
    QLabel *imageLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IncidentWidget)
    {
        if (IncidentWidget->objectName().isEmpty())
            IncidentWidget->setObjectName("IncidentWidget");
        IncidentWidget->resize(400, 250);
        IncidentWidget->setStyleSheet(QString::fromUtf8("#IncidentWidget {\n"
"    background-color: #2b2b2b;\n"
"    border: 1px solid #444;\n"
"    border-radius: 8px;\n"
"    margin-top: 5px;\n"
"    margin-bottom: 5px;\n"
"}\n"
"QLabel {\n"
"    color: #ffffff;\n"
"    background-color: transparent;\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        titleLabel = new QLabel(IncidentWidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setWordWrap(true);

        verticalLayout->addWidget(titleLabel);

        userInfoLabel = new QLabel(IncidentWidget);
        userInfoLabel->setObjectName("userInfoLabel");
        QFont font1;
        font1.setItalic(true);
        userInfoLabel->setFont(font1);
        userInfoLabel->setStyleSheet(QString::fromUtf8("color: #aaa;"));

        verticalLayout->addWidget(userInfoLabel);

        timestampLabel = new QLabel(IncidentWidget);
        timestampLabel->setObjectName("timestampLabel");
        timestampLabel->setFont(font1);
        timestampLabel->setStyleSheet(QString::fromUtf8("color: #aaa; margin-bottom: 5px;"));

        verticalLayout->addWidget(timestampLabel);

        line = new QFrame(IncidentWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        descriptionLabel = new QLabel(IncidentWidget);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setStyleSheet(QString::fromUtf8("margin-top: 5px;"));
        descriptionLabel->setWordWrap(true);

        verticalLayout->addWidget(descriptionLabel);

        imageLabel = new QLabel(IncidentWidget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setMinimumSize(QSize(0, 0));
        imageLabel->setMaximumSize(QSize(16777215, 200));

        verticalLayout->addWidget(imageLabel);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(IncidentWidget);

        QMetaObject::connectSlotsByName(IncidentWidget);
    } // setupUi

    void retranslateUi(QWidget *IncidentWidget)
    {
        IncidentWidget->setWindowTitle(QCoreApplication::translate("IncidentWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("IncidentWidget", "Incident Title", nullptr));
        userInfoLabel->setText(QCoreApplication::translate("IncidentWidget", "by username (user@email.com)", nullptr));
        timestampLabel->setText(QCoreApplication::translate("IncidentWidget", "timestamp", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("IncidentWidget", "Description of the incident goes here...", nullptr));
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IncidentWidget: public Ui_IncidentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCIDENTWIDGET_H
