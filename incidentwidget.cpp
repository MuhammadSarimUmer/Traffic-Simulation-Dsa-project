#include "incidentwidget.h"
#include "ui_incidentwidget.h"
#include <QPixmap>

IncidentWidget::IncidentWidget(const Incident& incident, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncidentWidget)
{
    ui->setupUi(this);

    // Set data
    ui->titleLabel->setText(incident.title);
    ui->userInfoLabel->setText(QString("Posted by: %1 (%2)")
                                   .arg(incident.username)
                                   .arg(incident.email));
    ui->timestampLabel->setText(incident.timestamp.toString("MMM dd, yyyy - hh:mm AP"));
    ui->descriptionLabel->setText(incident.description);

    // Handle image
    if (!incident.imagePath.isEmpty()) {
        QPixmap pixmap(incident.imagePath);
        if (!pixmap.isNull()) {
            // Scale pixmap to fit the label while keeping aspect ratio
            ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(),
                                                    200, // Max height of 200px
                                                    Qt::KeepAspectRatio,
                                                    Qt::SmoothTransformation));
            ui->imageLabel->setMinimumHeight(100); // Ensure it has some height
        } else {
            ui->imageLabel->setText("(Image failed to load: " + incident.imagePath + ")");
            ui->imageLabel->setVisible(true);
            ui->imageLabel->setWordWrap(true);
        }
    } else {
        // No image, hide the label
        ui->imageLabel->setVisible(false);
    }

    // Adjust size to fit content
    adjustSize();
}

IncidentWidget::~IncidentWidget()
{
    delete ui;
}
