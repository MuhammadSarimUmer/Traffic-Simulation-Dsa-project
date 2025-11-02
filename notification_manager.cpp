#include "notification_manager.h"
#include <QDebug>

NotificationManager::NotificationManager(QObject *parent)
    : QObject(parent)
{
}

void NotificationManager::sendCongestionEmail(const QString &recipient,
                                              int vehicleId,
                                              const QString &subject,
                                              const QString &body)
{
    // --- Purely simulated email (no real network calls) ---
    qDebug() << "=== SIMULATED EMAIL NOTIFICATION ===";
    qDebug() << "To:" << recipient;
    qDebug() << "Vehicle ID:" << vehicleId;
    qDebug() << "Subject:" << subject;
    qDebug() << "Body:" << body;
    qDebug() << "Timestamp:" << QDateTime::currentDateTime().toString();
    qDebug() << "===================================";

    emit emailSent(recipient, subject, body, QDateTime::currentDateTime());
}
