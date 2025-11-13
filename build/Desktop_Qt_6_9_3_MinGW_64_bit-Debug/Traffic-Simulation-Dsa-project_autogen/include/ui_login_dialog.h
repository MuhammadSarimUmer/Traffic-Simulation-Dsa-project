/********************************************************************************
** Form generated from reading UI file 'login_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_DIALOG_H
#define UI_LOGIN_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *loginForm;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *usernameLineEdit;
    QHBoxLayout *passwordLayout;
    QLineEdit *passwordLineEdit;
    QPushButton *togglePasswordButton;
    QLabel *statusLabel;
    QPushButton *loginButton;
    QPushButton *signupButton;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(800, 600);
        LoginDialog->setStyleSheet(QString::fromUtf8("/* --- Main Dialog --- */\n"
"QWidget#LoginDialog {\n"
"        background-image: url(:/images/login_background.png);\n"
"        background-repeat: no-repeat;\n"
"        background-position: center;\n"
"        background-attachment: fixed;\n"
"}\n"
"\n"
"/* --- Centered Form Card --- */\n"
"QFrame#loginForm {\n"
"        background-color: rgba(0, 0, 0, 0.75);\n"
"        border-radius: 20px;\n"
"        max-width: 450px;\n"
"        min-width: 450px;\n"
"        padding: 20px;\n"
"}\n"
"\n"
"/* --- Labels inside the card --- */\n"
"QFrame#loginForm QLabel {\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 14px;\n"
"}\n"
"QFrame#loginForm QLabel#titleLabel {\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 24px;\n"
"        padding-bottom: 10px;\n"
"}\n"
"QFrame#loginForm QLabel#statusLabel {\n"
"        color: #FFD700; /* Gold */\n"
"}\n"
"\n"
"/* --- Line Edits inside the card --- */\n"
"QFrame#loginForm QLineEdit {\n"
"        background-color:"
                        " rgba(0, 0, 0, 0.6);\n"
"        border: 1px solid #00AEEF;\n"
"        border-radius: 15px;\n"
"        padding: 12px;\n"
"        padding-right: 45px;\n"
"        color: white;\n"
"        font-size: 14px;\n"
"}\n"
"QFrame#loginForm QLineEdit:focus {\n"
"        border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"/* --- Password Toggle Button --- */\n"
"QFrame#loginForm QPushButton#togglePasswordButton {\n"
"        background-color: transparent;\n"
"        border: none;\n"
"        padding: 0px;\n"
"        margin: 0px;\n"
"        min-width: 30px;\n"
"        max-width: 30px;\n"
"        min-height: 30px;\n"
"        max-height: 30px;\n"
"}\n"
"QFrame#loginForm QPushButton#togglePasswordButton:hover {\n"
"        background-color: rgba(255, 255, 255, 0.1);\n"
"        border-radius: 5px;\n"
"}\n"
"\n"
"/* --- Buttons inside the card --- */\n"
"QFrame#loginForm QPushButton {\n"
"        background-color: #00AEEF;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 14px;\n"
"        border"
                        "-radius: 15px;\n"
"        padding: 12px;\n"
"        margin-top: 10px;\n"
"}\n"
"QFrame#loginForm QPushButton:hover {\n"
"        background-color: #009BCF;\n"
"}\n"
"QFrame#loginForm QPushButton:pressed {\n"
"        background-color: #007AAC;\n"
"}\n"
"\n"
"/* --- 'Sign Up' Button --- */\n"
"QFrame#loginForm QPushButton#signupButton {\n"
"        background-color: transparent;\n"
"        border: 2px solid #00AEEF;\n"
"}\n"
"QFrame#loginForm QPushButton#signupButton:hover {\n"
"        background-color: rgba(0, 174, 239, 0.2);\n"
"}\n"
"QFrame#loginForm QPushButton#signupButton:pressed {\n"
"        background-color: rgba(0, 174, 239, 0.4);\n"
"}\n"
"\n"
"/* --- 'Exit' Button --- */\n"
"QFrame#loginForm QPushButton#exitButton {\n"
"        background-color: #D32F2F; /* Red */\n"
"        border: none;\n"
"}\n"
"QFrame#loginForm QPushButton#exitButton:hover {\n"
"        background-color: #E53935; /* Lighter Red */\n"
"}\n"
"QFrame#loginForm QPushButton#exitButton:pressed {\n"
"        background-color: #C62"
                        "828; /* Darker Red */\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(LoginDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 123, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loginForm = new QFrame(LoginDialog);
        loginForm->setObjectName("loginForm");
        loginForm->setFrameShape(QFrame::StyledPanel);
        loginForm->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(loginForm);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(loginForm);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        usernameLineEdit = new QLineEdit(loginForm);
        usernameLineEdit->setObjectName("usernameLineEdit");

        verticalLayout->addWidget(usernameLineEdit);

        passwordLayout = new QHBoxLayout();
        passwordLayout->setSpacing(0);
        passwordLayout->setObjectName("passwordLayout");
        passwordLineEdit = new QLineEdit(loginForm);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        passwordLayout->addWidget(passwordLineEdit);

        togglePasswordButton = new QPushButton(loginForm);
        togglePasswordButton->setObjectName("togglePasswordButton");
        togglePasswordButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        passwordLayout->addWidget(togglePasswordButton);


        verticalLayout->addLayout(passwordLayout);

        statusLabel = new QLabel(loginForm);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setWordWrap(true);

        verticalLayout->addWidget(statusLabel);

        loginButton = new QPushButton(loginForm);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        signupButton = new QPushButton(loginForm);
        signupButton->setObjectName("signupButton");

        verticalLayout->addWidget(signupButton);

        exitButton = new QPushButton(loginForm);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);


        horizontalLayout->addWidget(loginForm);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 122, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginDialog", "TrafficSim Login", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Username", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        togglePasswordButton->setText(QCoreApplication::translate("LoginDialog", "\360\237\221\201", nullptr));
        statusLabel->setText(QString());
        loginButton->setText(QCoreApplication::translate("LoginDialog", "LOGIN", nullptr));
        signupButton->setText(QCoreApplication::translate("LoginDialog", "CREATE AN ACCOUNT", nullptr));
        exitButton->setText(QCoreApplication::translate("LoginDialog", "EXIT APPLICATION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_DIALOG_H
