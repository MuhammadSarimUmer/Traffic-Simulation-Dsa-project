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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IncidentWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *iconLabel;
    QVBoxLayout *titleInfoLayout;
    QLabel *titleLabel;
    QLabel *timestampLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *userInfoLabel;
    QFrame *line;
    QLabel *descriptionLabel;
    QLabel *imageLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *footerLayout;
    QLabel *locationLabel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *IncidentWidget)
    {
        if (IncidentWidget->objectName().isEmpty())
            IncidentWidget->setObjectName("IncidentWidget");
        IncidentWidget->resize(420, 240);
        IncidentWidget->setStyleSheet(QString::fromUtf8("#IncidentWidget {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 rgba(255, 255, 255, 0.08),\n"
"                                stop:1 rgba(255, 255, 255, 0.04));\n"
"    border: 1px solid rgba(255, 255, 255, 0.15);\n"
"    border-radius: 12px;\n"
"    margin: 4px;\n"
"}\n"
"#IncidentWidget:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 rgba(255, 255, 255, 0.12),\n"
"                                stop:1 rgba(255, 255, 255, 0.06));\n"
"    border: 1px solid rgba(33, 150, 243, 0.4);\n"
"}\n"
"QLabel {\n"
"    color: #ffffff;\n"
"    background-color: transparent;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}"));
        verticalLayout = new QVBoxLayout(IncidentWidget);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        headerLayout = new QHBoxLayout();
        headerLayout->setSpacing(10);
        headerLayout->setObjectName("headerLayout");
        iconLabel = new QLabel(IncidentWidget);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setMinimumSize(QSize(36, 36));
        iconLabel->setMaximumSize(QSize(36, 36));
        iconLabel->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                    stop:0 #2196F3, stop:1 #0b7dda);\n"
"border-radius: 18px;\n"
"font-size: 18px;\n"
"padding: 6px;"));
        iconLabel->setAlignment(Qt::AlignCenter);

        headerLayout->addWidget(iconLabel);

        titleInfoLayout = new QVBoxLayout();
        titleInfoLayout->setSpacing(3);
        titleInfoLayout->setObjectName("titleInfoLayout");
        titleLabel = new QLabel(IncidentWidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("color: #ffffff;"));
        titleLabel->setWordWrap(true);

        titleInfoLayout->addWidget(titleLabel);

        timestampLabel = new QLabel(IncidentWidget);
        timestampLabel->setObjectName("timestampLabel");
        QFont font1;
        font1.setPointSize(8);
        timestampLabel->setFont(font1);
        timestampLabel->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.5);"));

        titleInfoLayout->addWidget(timestampLabel);


        headerLayout->addLayout(titleInfoLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(headerLayout);

        userInfoLabel = new QLabel(IncidentWidget);
        userInfoLabel->setObjectName("userInfoLabel");
        QFont font2;
        font2.setPointSize(8);
        font2.setItalic(false);
        userInfoLabel->setFont(font2);
        userInfoLabel->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.6);\n"
"background: rgba(255, 255, 255, 0.05);\n"
"padding: 5px 10px;\n"
"border-radius: 6px;"));

        verticalLayout->addWidget(userInfoLabel);

        line = new QFrame(IncidentWidget);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0.1);\n"
"height: 1px;"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        descriptionLabel = new QLabel(IncidentWidget);
        descriptionLabel->setObjectName("descriptionLabel");
        QFont font3;
        font3.setPointSize(9);
        descriptionLabel->setFont(font3);
        descriptionLabel->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.85);\n"
"line-height: 1.5;\n"
"padding: 6px 0;"));
        descriptionLabel->setWordWrap(true);

        verticalLayout->addWidget(descriptionLabel);

        imageLabel = new QLabel(IncidentWidget);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setStyleSheet(QString::fromUtf8("border: 2px solid rgba(255, 255, 255, 0.1);\n"
"border-radius: 10px;\n"
"background-color: rgba(0, 0, 0, 0.2);\n"
"padding: 3px;"));
        imageLabel->setMinimumSize(QSize(0, 0));
        imageLabel->setMaximumSize(QSize(16777215, 160));

        verticalLayout->addWidget(imageLabel);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        footerLayout = new QHBoxLayout();
        footerLayout->setSpacing(6);
        footerLayout->setObjectName("footerLayout");
        locationLabel = new QLabel(IncidentWidget);
        locationLabel->setObjectName("locationLabel");
        locationLabel->setFont(font1);
        locationLabel->setStyleSheet(QString::fromUtf8("color: rgba(33, 150, 243, 0.9);\n"
"background: rgba(33, 150, 243, 0.15);\n"
"padding: 4px 8px;\n"
"border-radius: 5px;"));

        footerLayout->addWidget(locationLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        footerLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(footerLayout);


        retranslateUi(IncidentWidget);

        QMetaObject::connectSlotsByName(IncidentWidget);
    } // setupUi

    void retranslateUi(QWidget *IncidentWidget)
    {
        IncidentWidget->setWindowTitle(QCoreApplication::translate("IncidentWidget", "Form", nullptr));
        iconLabel->setText(QCoreApplication::translate("IncidentWidget", "\342\232\240\357\270\217", nullptr));
        titleLabel->setText(QCoreApplication::translate("IncidentWidget", "Incident Title", nullptr));
        timestampLabel->setText(QCoreApplication::translate("IncidentWidget", "\360\237\225\220 2 hours ago", nullptr));
        userInfoLabel->setText(QCoreApplication::translate("IncidentWidget", "\360\237\221\244 by username \342\200\242 user@email.com", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("IncidentWidget", "Description of the incident goes here. This provides detailed information about what happened.", nullptr));
        imageLabel->setText(QString());
        locationLabel->setText(QCoreApplication::translate("IncidentWidget", "\360\237\223\215 Karachi, Pakistan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncidentWidget: public Ui_IncidentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCIDENTWIDGET_H
