/********************************************************************************
** Form generated from reading UI file 'signup_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_DIALOG_H
#define UI_SIGNUP_DIALOG_H

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

class Ui_SignUpDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *signupForm;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *emailLineEdit;
    QHBoxLayout *passwordLayout;
    QLineEdit *passwordLineEdit;
    QPushButton *togglePasswordButton;
    QHBoxLayout *confirmPasswordLayout;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *toggleConfirmPasswordButton;
    QLabel *statusLabel;
    QPushButton *signupButton;
    QPushButton *backButton;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *SignUpDialog)
    {
        if (SignUpDialog->objectName().isEmpty())
            SignUpDialog->setObjectName("SignUpDialog");
        SignUpDialog->resize(800, 600);
        SignUpDialog->setStyleSheet(QString::fromUtf8("/* --- Main Dialog --- */\n"
"QWidget#SignUpDialog {\n"
"        background-image: url(:/images/login_background.png);\n"
"        background-repeat: no-repeat;\n"
"        background-position: center;\n"
"        background-attachment: fixed;\n"
"}\n"
"\n"
"/* --- Centered Form Card --- */\n"
"QFrame#signupForm {\n"
"        background-color: rgba(0, 0, 0, 0.75);\n"
"        border-radius: 20px;\n"
"        max-width: 450px;\n"
"        min-width: 450px;\n"
"        padding: 20px;\n"
"}\n"
"\n"
"/* --- Labels inside the card --- */\n"
"QFrame#signupForm QLabel {\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 14px;\n"
"}\n"
"QFrame#signupForm QLabel#titleLabel {\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 24px;\n"
"        padding-bottom: 10px;\n"
"}\n"
"QFrame#signupForm QLabel#statusLabel {\n"
"        color: #FFD700; /* Gold */\n"
"}\n"
"\n"
"/* --- Line Edits inside the card --- */\n"
"QFrame#signupForm QLineEdit {\n"
"        background-"
                        "color: rgba(0, 0, 0, 0.6);\n"
"        border: 1px solid #00AEEF;\n"
"        border-radius: 15px;\n"
"        padding: 12px;\n"
"        padding-right: 45px;\n"
"        color: white;\n"
"        font-size: 14px;\n"
"}\n"
"QFrame#signupForm QLineEdit:focus {\n"
"        border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"/* --- Password Toggle Button --- */\n"
"QFrame#signupForm QPushButton#togglePasswordButton,\n"
"QFrame#signupForm QPushButton#toggleConfirmPasswordButton {\n"
"        background-color: transparent;\n"
"        border: none;\n"
"        padding: 0px;\n"
"        margin: 0px;\n"
"        min-width: 30px;\n"
"        max-width: 30px;\n"
"        min-height: 30px;\n"
"        max-height: 30px;\n"
"}\n"
"QFrame#signupForm QPushButton#togglePasswordButton:hover,\n"
"QFrame#signupForm QPushButton#toggleConfirmPasswordButton:hover {\n"
"        background-color: rgba(255, 255, 255, 0.1);\n"
"        border-radius: 5px;\n"
"}\n"
"\n"
"/* --- Buttons inside the card --- */\n"
"QFrame#signupForm QPushButton {\n"
""
                        "        background-color: #00AEEF;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        font-size: 14px;\n"
"        border-radius: 15px;\n"
"        padding: 12px;\n"
"        margin-top: 10px;\n"
"}\n"
"QFrame#signupForm QPushButton:hover {\n"
"        background-color: #009BCF;\n"
"}\n"
"QFrame#signupForm QPushButton:pressed {\n"
"        background-color: #007AAC;\n"
"}\n"
"\n"
"/* --- 'Back' Button --- */\n"
"QFrame#signupForm QPushButton#backButton {\n"
"        background-color: transparent;\n"
"        border: 2px solid #00AEEF;\n"
"}\n"
"QFrame#signupForm QPushButton#backButton:hover {\n"
"        background-color: rgba(0, 174, 239, 0.2);\n"
"}\n"
"QFrame#signupForm QPushButton#backButton:pressed {\n"
"        background-color: rgba(0, 174, 239, 0.4);\n"
"}\n"
"\n"
"/* --- 'Exit' Button --- */\n"
"QFrame#signupForm QPushButton#exitButton {\n"
"        background-color: #D32F2F; /* Red */\n"
"        border: none;\n"
"}\n"
"QFrame#signupForm QPushButton#exitButton:hover {\n"
"        ba"
                        "ckground-color: #E53935; /* Lighter Red */\n"
"}\n"
"QFrame#signupForm QPushButton#exitButton:pressed {\n"
"        background-color: #C62828; /* Darker Red */\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(SignUpDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 123, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        signupForm = new QFrame(SignUpDialog);
        signupForm->setObjectName("signupForm");
        signupForm->setFrameShape(QFrame::StyledPanel);
        signupForm->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(signupForm);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(signupForm);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        usernameLineEdit = new QLineEdit(signupForm);
        usernameLineEdit->setObjectName("usernameLineEdit");

        verticalLayout->addWidget(usernameLineEdit);

        emailLineEdit = new QLineEdit(signupForm);
        emailLineEdit->setObjectName("emailLineEdit");

        verticalLayout->addWidget(emailLineEdit);

        passwordLayout = new QHBoxLayout();
        passwordLayout->setSpacing(0);
        passwordLayout->setObjectName("passwordLayout");
        passwordLineEdit = new QLineEdit(signupForm);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        passwordLayout->addWidget(passwordLineEdit);

        togglePasswordButton = new QPushButton(signupForm);
        togglePasswordButton->setObjectName("togglePasswordButton");
        togglePasswordButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        passwordLayout->addWidget(togglePasswordButton);


        verticalLayout->addLayout(passwordLayout);

        confirmPasswordLayout = new QHBoxLayout();
        confirmPasswordLayout->setSpacing(0);
        confirmPasswordLayout->setObjectName("confirmPasswordLayout");
        confirmPasswordLineEdit = new QLineEdit(signupForm);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

        confirmPasswordLayout->addWidget(confirmPasswordLineEdit);

        toggleConfirmPasswordButton = new QPushButton(signupForm);
        toggleConfirmPasswordButton->setObjectName("toggleConfirmPasswordButton");
        toggleConfirmPasswordButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        confirmPasswordLayout->addWidget(toggleConfirmPasswordButton);


        verticalLayout->addLayout(confirmPasswordLayout);

        statusLabel = new QLabel(signupForm);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setWordWrap(true);

        verticalLayout->addWidget(statusLabel);

        signupButton = new QPushButton(signupForm);
        signupButton->setObjectName("signupButton");

        verticalLayout->addWidget(signupButton);

        backButton = new QPushButton(signupForm);
        backButton->setObjectName("backButton");

        verticalLayout->addWidget(backButton);

        exitButton = new QPushButton(signupForm);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);


        horizontalLayout->addWidget(signupForm);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 122, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(SignUpDialog);

        QMetaObject::connectSlotsByName(SignUpDialog);
    } // setupUi

    void retranslateUi(QDialog *SignUpDialog)
    {
        SignUpDialog->setWindowTitle(QCoreApplication::translate("SignUpDialog", "Sign Up", nullptr));
        titleLabel->setText(QCoreApplication::translate("SignUpDialog", "Create Account", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("SignUpDialog", "Username", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("SignUpDialog", "Email", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("SignUpDialog", "Password", nullptr));
        togglePasswordButton->setText(QCoreApplication::translate("SignUpDialog", "\360\237\221\201", nullptr));
        confirmPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("SignUpDialog", "Confirm Password", nullptr));
        toggleConfirmPasswordButton->setText(QCoreApplication::translate("SignUpDialog", "\360\237\221\201", nullptr));
        statusLabel->setText(QString());
        signupButton->setText(QCoreApplication::translate("SignUpDialog", "SIGN UP", nullptr));
        backButton->setText(QCoreApplication::translate("SignUpDialog", "BACK TO LOGIN", nullptr));
        exitButton->setText(QCoreApplication::translate("SignUpDialog", "EXIT APPLICATION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUpDialog: public Ui_SignUpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_DIALOG_H
