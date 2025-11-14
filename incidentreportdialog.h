#ifndef INCIDENTREPORTDIALOG_H
#define INCIDENTREPORTDIALOG_H

#include <QDialog>

namespace Ui {
class IncidentReportDialog;
}

class IncidentReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IncidentReportDialog(QWidget *parent = nullptr);
    ~IncidentReportDialog();

    // Public getters to retrieve the data after submission
    QString getTitle() const;
    QString getDescription() const;
    QString getImagePath() const;

private slots:
    void on_browseButton_clicked();
    void on_submitButton_clicked();

private:
    Ui::IncidentReportDialog *ui;
    QString m_imagePath; // To store the selected image file path
};

#endif // INCIDENTREPORTDIALOG_H
