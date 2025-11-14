#include "incidentfeeddialog.h"
#include "ui_incidentfeeddialog.h"
#include "incidentreportdialog.h" // The form
#include "incidentwidget.h"       // The custom post widget
#include <QDebug>
#include <QMessageBox>
#include <QLabel>                 // <-- ADDED
#include <QLayoutItem>            // <-- ADDED

IncidentFeedDialog::IncidentFeedDialog(DatabaseManager *dbManager,
                                       const QString& username,
                                       const QString& email,
                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncidentFeedDialog),
    m_dbManager(dbManager),
    m_username(username),
    m_email(email)
{
    ui->setupUi(this);
    setWindowTitle("Live Incident Feed");

    // Set a minimum size
    setMinimumSize(500, 600);

    // Load incidents when the dialog is first opened
    loadIncidents();
}

IncidentFeedDialog::~IncidentFeedDialog()
{
    delete ui;
}

void IncidentFeedDialog::clearFeedLayout()
{
    QLayoutItem *child;
    while ((child = ui->feedLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget(); // Delete the widget
        }
        delete child; // Delete the layout item
    }
}

void IncidentFeedDialog::loadIncidents()
{
    if (!m_dbManager) return;

    // Clear the existing feed
    clearFeedLayout();

    // Get all incidents from the database
    QList<Incident> incidents = m_dbManager->getAllIncidents();

    if (incidents.isEmpty()) {
        QLabel *emptyLabel = new QLabel("The incident feed is empty.\nBe the first to report something!", this);
        emptyLabel->setStyleSheet("color: #888; font-style: italic; padding: 20px;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setWordWrap(true);
        ui->feedLayout->addWidget(emptyLabel);
    } else {
        // Add each incident as a new widget
        for (const Incident& incident : incidents) {
            IncidentWidget *widget = new IncidentWidget(incident, ui->scrollAreaWidgetContents);
            ui->feedLayout->addWidget(widget);
        }
    }

    // Add a spacer at the bottom to push widgets to the top
    ui->feedLayout->addStretch(1);
}

void IncidentFeedDialog::on_refreshButton_clicked()
{
    loadIncidents();
}

void IncidentFeedDialog::on_reportIncidentButton_clicked()
{
    // This is the flow you described:
    // 1. Open the form
    IncidentReportDialog reportForm(this);

    // 2. Hide this feed window
    this->hide();

    // 3. Show the form modally.
    //    The code will pause here until the form is submitted or cancelled.
    int result = reportForm.exec();

    // 4. Check if the user clicked "Submit"
    if (result == QDialog::Accepted)
    {
        // Get the data from the form
        QString title = reportForm.getTitle();
        QString description = reportForm.getDescription();
        QString imagePath = reportForm.getImagePath();

        // 5. Save the new incident to the database
        if (m_dbManager) {
            bool success = m_dbManager->addIncident(title, description, imagePath, m_username, m_email);
            if (!success) {
                QMessageBox::warning(this, "Database Error", "Could not save your incident report. Please try again.");
            }
        }

        // 6. Reload the feed with the new post
        loadIncidents();
    }

    // 7. Show this feed window again, whether the post was submitted or cancelled
    this->show();
}
