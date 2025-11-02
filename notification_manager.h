#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <QObject>
#include <QDateTime>

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    explicit NotificationManager(QObject *parent = nullptr);

    // Function to simulate sending congestion emails
    void sendCongestionEmail(const QString &recipient,
                             int vehicleId,
                             const QString &subject,
                             const QString &body);

signals:
    void emailSent(const QString &recipient,
                   const QString &subject,
                   const QString &body,
                   const QDateTime &timestamp);
};

#endif // NOTIFICATION_MANAGER_H
