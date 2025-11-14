#ifndef INCIDENTWIDGET_H
#define INCIDENTWIDGET_H

#include <QWidget>
#include "database_manager.h" // For the Incident struct

namespace Ui {
class IncidentWidget;
}

class IncidentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IncidentWidget(const Incident& incident, QWidget *parent = nullptr);
    ~IncidentWidget();

private:
    Ui::IncidentWidget *ui;
};

#endif // INCIDENTWIDGET_H
