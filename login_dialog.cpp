#include "login_dialog.h"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(DatabaseManager *dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    dbManager(dbManager),
    passwordVisible(false)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    // Set up animation
    setWindowOpacity(0.0); // Start fully transparent
    animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300); // 300ms fade

    // Position the toggle button inside the password field
    ui->togglePasswordButton->setCursor(Qt::PointingHandCursor);

    // Set initial icon
    ui->togglePasswordButton->setText("👁");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// --- Animation Functions ---

void LoginDialog::showEvent(QShowEvent *event)
{
    // Clear fields and status when dialog is shown
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->statusLabel->clear();

    // Reset password visibility
    passwordVisible = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->togglePasswordButton->setText("👁");

    startFadeIn();
    QDialog::showEvent(event);
}

void LoginDialog::startFadeIn()
{
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}

void LoginDialog::startFadeOutAndClose(int result)
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

void LoginDialog::done(int r)
{
    // If we are just switching to signup, do it *instantly*
    if (r == ShowSignUp) {
        QDialog::done(r); // No animation
    } else {
        // For login (Accept) or exit (Reject), fade out
        startFadeOutAndClose(r);
    }
}

void LoginDialog::accept()
{
    // Override accept to trigger animated fade-out
    startFadeOutAndClose(QDialog::Accepted);
}

void LoginDialog::reject()
{
    // Override reject (for 'X' button) to trigger animated fade-out
    startFadeOutAndClose(QDialog::Rejected);
}


// --- Button Slots ---

void LoginDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->statusLabel->setText("Please enter both username and password.");
        return;
    }

    if (dbManager->checkLogin(username, password)) {
        accept();
    } else {
        ui->statusLabel->setText("Invalid username or password.");
    }
}

void LoginDialog::on_signupButton_clicked()
{
    // This will call our instant done() function
    done(ShowSignUp);
}

void LoginDialog::on_exitButton_clicked()
{
    // This will call our animated reject() function
    reject();
}

void LoginDialog::on_togglePasswordButton_clicked()
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
