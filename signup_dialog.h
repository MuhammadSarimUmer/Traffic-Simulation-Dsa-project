#ifndef SIGNUP_DIALOG_H
#define SIGNUP_DIALOG_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QShowEvent>
#include "database_manager.h"

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    // This enum tells main.cpp to switch to login *without* animating
    enum DialogCode { ShowLogin = QDialog::Accepted + 1 };

    explicit SignUpDialog(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~SignUpDialog();

    // Re-implemented to control animation
    virtual void accept() override;
    virtual void reject() override;
    virtual void done(int r) override;

protected:
    // Re-implemented to trigger fade-in
    virtual void showEvent(QShowEvent *event) override;

private slots:
    void on_signupButton_clicked();
    void on_backButton_clicked();
    void on_exitButton_clicked();
    void on_togglePasswordButton_clicked();
    void on_toggleConfirmPasswordButton_clicked();

private:
    void startFadeIn();
    void startFadeOutAndClose(int result);

    Ui::SignUpDialog *ui;
    DatabaseManager *dbManager;
    QPropertyAnimation *animation;
    bool passwordVisible;
    bool confirmPasswordVisible;
};

#endif // SIGNUP_DIALOG_H
