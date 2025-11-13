#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initDatabase();
    // Updated to accept email
    bool addUser(const QString& username, const QString& email, const QString& password);
    bool checkLogin(const QString& username, const QString& password);

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
