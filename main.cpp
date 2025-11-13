#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"
#include "login_dialog.h"
#include "signup_dialog.h"
#include "database_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    DatabaseManager dbManager;
    if (!dbManager.initDatabase()) {
        qCritical("Failed to initialize database. Exiting.");
        return 1;
    }

    LoginDialog loginDialog(&dbManager);
    SignUpDialog signupDialog(&dbManager);

    MainWindow w;

    bool loggedIn = false;
    bool showLogin = true; // Start with login dialog

    while(true)
    {
        int dialogResult;

        if (showLogin) {
            // --- Show Login Dialog ---
            dialogResult = loginDialog.exec();

            if (dialogResult == QDialog::Accepted) {
                // Login was successful!
                loggedIn = true;
                break; // Exit main loop
            }
            else if (dialogResult == LoginDialog::ShowSignUp) {
                // User clicked "Create Account", show Sign Up next
                showLogin = false;
            }
            else if (dialogResult == QDialog::Rejected) {
                // User clicked "Exit App" or 'X' on login screen
                loggedIn = false;
                break; // Exit main loop
            }
        }
        else {
            // --- Show Sign Up Dialog ---
            dialogResult = signupDialog.exec();

            if (dialogResult == QDialog::Accepted) {
                // Signup successful (shouldn't happen now, but handle it)
                showLogin = true;
            }
            else if (dialogResult == SignUpDialog::ShowLogin) {
                // User clicked "Back" or successful signup
                showLogin = true;
            }
            else if (dialogResult == QDialog::Rejected) {
                // User clicked "Exit App" or 'X' on signup screen
                loggedIn = false;
                break; // Exit main loop
            }
        }
    }

    if (loggedIn)
    {
        // User is logged in, show the main app
        w.showMaximized();
        return a.exec();
    }
    else
    {
        // User exited without logging in
        return 0;
    }
}
