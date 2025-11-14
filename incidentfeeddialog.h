#ifndef INCIDENTFEEDDIALOG_H
#define INCIDENTFEEDDIALOG_H

#include <QDialog>
#include "database_manager.h" // Needs this to read/write

namespace Ui {
class IncidentFeedDialog;
}

class IncidentFeedDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor needs user info and the db manager
    explicit IncidentFeedDialog(DatabaseManager *dbManager,
                                const QString& username,
                                const QString& email,
                                QWidget *parent = nullptr);
    ~IncidentFeedDialog();

private slots:
    void on_reportIncidentButton_clicked();
    void on_refreshButton_clicked();

private:
    void loadIncidents();
    void clearFeedLayout();

    Ui::IncidentFeedDialog *ui;
    DatabaseManager *m_dbManager;
    QString m_username;
    QString m_email;
};

#endif // INCIDENTFEEDDIALOG_H
