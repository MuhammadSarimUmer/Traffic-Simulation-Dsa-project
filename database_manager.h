#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QList>      // <-- ADDED
#include <QDateTime>  // <-- ADDED

// --- NEW DATA STRUCTURE ---
// Represents a single incident post
struct Incident {
    int id;
    QString title;
    QString description;
    QString imagePath;
    QString username;
    QString email;
    QDateTime timestamp;
};
// --- END NEW ---


class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initDatabase();
    bool addUser(const QString& username, const QString& email, const QString& password);
    bool checkLogin(const QString& username, const QString& password);

    // --- NEW PUBLIC FUNCTIONS ---
    QString getEmailForUsername(const QString& username);
    bool addIncident(const QString& title, const QString& description, const QString& imagePath, const QString& username, const QString& email);
    QList<Incident> getAllIncidents();
    // --- END NEW ---

    // Public enum to report specific errors
    enum AddUserError {
        Success,
        UsernameTaken,
        EmailTaken,
        UnknownError
    };

    // Getter for the last error
    AddUserError lastAddUserError() const;


private:
    QString hashPassword(const QString& password);
    QSqlDatabase db;
    AddUserError lastError; // Private variable to store the error
};

#endif // DATABASE_MANAGER_H
