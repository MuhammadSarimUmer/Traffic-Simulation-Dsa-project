#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QShowEvent>
#include "database_manager.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    enum DialogCode { ShowSignUp = QDialog::Accepted + 1 };

    explicit LoginDialog(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~LoginDialog();

    // --- NEW PUBLIC FUNCTION ---
    QString getUsername() const;
    // --- END NEW ---

    // Re-implemented to control animation
    virtual void accept() override;
    virtual void reject() override;
    virtual void done(int r) override;

protected:
    // Re-implemented to trigger fade-in
    virtual void showEvent(QShowEvent *event) override;

private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();
    void on_exitButton_clicked();
    void on_togglePasswordButton_clicked();

private:
    void startFadeIn();
    void startFadeOutAndClose(int result);

    Ui::LoginDialog *ui;
    DatabaseManager *dbManager;
    QPropertyAnimation *animation;
    bool passwordVisible;
};

#endif // LOGIN_DIALOG_H
