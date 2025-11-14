#include "incidentreportdialog.h"
#include "ui_incidentreportdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir> // <-- ADDED

IncidentReportDialog::IncidentReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncidentReportDialog)
{
    ui->setupUi(this);
    setWindowTitle("Report New Incident");
}

IncidentReportDialog::~IncidentReportDialog()
{
    delete ui;
}

void IncidentReportDialog::on_browseButton_clicked()
{
    // Open a file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Select Image",
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        m_imagePath = filePath;
        ui->imagePathLineEdit->setText(filePath);
    }
}

void IncidentReportDialog::on_submitButton_clicked()
{
    // Validate the input
    if (ui->titleLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter a title.");
        return;
    }
    if (ui->descriptionTextEdit->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please enter a description.");
        return;
    }

    // If all is valid, accept the dialog
    accept();
}

// --- Public Getters ---
QString IncidentReportDialog::getTitle() const
{
    return ui->titleLineEdit->text().trimmed();
}

QString IncidentReportDialog::getDescription() const
{
    return ui->descriptionTextEdit->toPlainText().trimmed();
}

QString IncidentReportDialog::getImagePath() const
{
    return m_imagePath;
}
