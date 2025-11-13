#include "database_manager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent), lastError(Success)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

DatabaseManager::AddUserError DatabaseManager::lastAddUserError() const
{
    return lastError;
}

bool DatabaseManager::initDatabase()
{
    if (!db.open()) {
        qWarning() << "Error: failed to open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    // Added 'email TEXT NOT NULL UNIQUE'
    bool success = query.exec("CREATE TABLE IF NOT EXISTS users ("
                              "username TEXT PRIMARY KEY, "
                              "email TEXT NOT NULL UNIQUE, "
                              "password_hash TEXT NOT NULL"
                              ");");
    if (!success) {
        qWarning() << "Error: failed to create table:" << query.lastError().text();
    }
    return success;
}

QString DatabaseManager::hashPassword(const QString& password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

// Updated to accept email
bool DatabaseManager::addUser(const QString& username, const QString& email, const QString& password)
{
    if (username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        lastError = UnknownError;
        return false;
    }

    QString hashedPassword = hashPassword(password);

    QSqlQuery query;
    // Updated query to include email
    query.prepare("INSERT INTO users (username, email, password_hash) "
                  "VALUES (:username, :email, :password)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        // Check what kind of error occurred
        QSqlError err = query.lastError();
        if (err.text().contains("UNIQUE constraint failed: users.username")) {
            lastError = UsernameTaken;
        } else if (err.text().contains("UNIQUE constraint failed: users.email")) {
            lastError = EmailTaken;
        } else {
            qWarning() << "Error: failed to add user:" << err.text();
            lastError = UnknownError;
        }
        return false;
    }

    lastError = Success;
    return true;
}

bool DatabaseManager::checkLogin(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qWarning() << "Error: failed to check login:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedHash = query.value(0).toString();
        QString providedHash = hashPassword(password);
        return (storedHash == providedHash);
    }

    // User not found
    return false;
}
