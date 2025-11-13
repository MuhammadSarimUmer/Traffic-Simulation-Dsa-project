#include "signup_dialog.h"
#include "ui_signup_dialog.h"
#include <QMessageBox>

SignUpDialog::SignUpDialog(DatabaseManager *dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog),
    dbManager(dbManager),
    passwordVisible(false),
    confirmPasswordVisible(false)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    // Set up animation
    setWindowOpacity(0.0); // Start fully transparent
    animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300); // 300ms fade

    // Position the toggle buttons inside the password fields
    ui->togglePasswordButton->setCursor(Qt::PointingHandCursor);
    ui->toggleConfirmPasswordButton->setCursor(Qt::PointingHandCursor);

    // Set initial icons
    ui->togglePasswordButton->setText("👁");
    ui->toggleConfirmPasswordButton->setText("👁");
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

// --- Animation Functions ---

void SignUpDialog::showEvent(QShowEvent *event)
{
    // Clear fields and status when dialog is shown
    ui->usernameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
    ui->statusLabel->clear();

    // Reset password visibility
    passwordVisible = false;
    confirmPasswordVisible = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->togglePasswordButton->setText("👁");
    ui->toggleConfirmPasswordButton->setText("👁");

    // When the dialog is shown, start the fade-in
    startFadeIn();
    QDialog::showEvent(event);
}

void SignUpDialog::startFadeIn()
{
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}

void SignUpDialog::startFadeOutAndClose(int result)
{
    disconnect(animation, &QPropertyAnimation::finished, nullptr, nullptr);

    // Connect the finished signal to the base QDialog::done() slot
    connect(animation, &QPropertyAnimation::finished, [this, result]() {
        QDialog::done(result);
    });

    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start();
}

// --- Overridden Close Functions ---

void SignUpDialog::done(int r)
{
    // If we are just switching back to login, do it *instantly*
    if (r == ShowLogin) {
        // No animation, just close and return the code
        QDialog::done(r);
    } else {
        // For success (Accept) or exit (Reject), fade out
        startFadeOutAndClose(r);
    }
}

void SignUpDialog::accept()
{
    // Override accept to trigger animated fade-out
    startFadeOutAndClose(QDialog::Accepted);
}

void SignUpDialog::reject()
{
    // Override reject (for 'X' button) to trigger animated fade-out and exit
    startFadeOutAndClose(QDialog::Rejected);
}

// --- Button Slots ---

void SignUpDialog::on_signupButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        ui->statusLabel->setText("All fields are required.");
        return;
    }

    // Simple email validation
    if (!email.contains('@') || !email.contains('.')) {
        ui->statusLabel->setText("Please enter a valid email address.");
        return;
    }

    if (password != confirmPassword) {
        ui->statusLabel->setText("Passwords do not match.");
        return;
    }

    // Try to add the user
    if (dbManager->addUser(username, email, password)) {
        QMessageBox::information(this, "Success", "Sign up successful! Please log in.");
        // Go back to login screen instantly after successful signup
        done(ShowLogin);
    } else {
        // Give specific errors
        switch(dbManager->lastAddUserError()) {
        case DatabaseManager::UsernameTaken:
            ui->statusLabel->setText("Error: This username is already taken.");
            break;
        case DatabaseManager::EmailTaken:
            ui->statusLabel->setText("Error: This email is already in use.");
            break;
        default:
            ui->statusLabel->setText("An unknown error occurred.");
            break;
        }
    }
}

void SignUpDialog::on_backButton_clicked()
{
    // Go back to login instantly
    done(ShowLogin);
}

void SignUpDialog::on_exitButton_clicked()
{
    // Exit with animation
    reject();
}

void SignUpDialog::on_togglePasswordButton_clicked()
{
    passwordVisible = !passwordVisible;

    if (passwordVisible) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setText("🙈"); // Eye with line through it (hidden)
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setText("👁"); // Open eye (visible)
    }
}

void SignUpDialog::on_toggleConfirmPasswordButton_clicked()
{
    confirmPasswordVisible = !confirmPasswordVisible;

    if (confirmPasswordVisible) {
        ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->toggleConfirmPasswordButton->setText("🙈"); // Eye with line through it (hidden)
    } else {
        ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
        ui->toggleConfirmPasswordButton->setText("👁"); // Open eye (visible)
    }
}
