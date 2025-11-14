#include "database_manager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QVariant> // <-- ADDED

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
    // 1. Create users table (existing code)
    bool success = query.exec("CREATE TABLE IF NOT EXISTS users ("
                              "username TEXT PRIMARY KEY, "
                              "email TEXT NOT NULL UNIQUE, "
                              "password_hash TEXT NOT NULL"
                              ");");
    if (!success) {
        qWarning() << "Error: failed to create users table:" << query.lastError().text();
        return false; // <-- Return on failure
    }

    // --- NEW CODE ---
    // 2. Create incidents table
    success = query.exec("CREATE TABLE IF NOT EXISTS incidents ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "title TEXT NOT NULL, "
                         "description TEXT NOT NULL, "
                         "image_path TEXT, "
                         "username TEXT NOT NULL, "
                         "email TEXT NOT NULL, "
                         "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
                         ");");
    if (!success) {
        qWarning() << "Error: failed to create incidents table:" << query.lastError().text();
    }
    // --- END NEW ---

    return success; // Return final status
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


// --- NEW FUNCTION IMPLEMENTATIONS ---

QString DatabaseManager::getEmailForUsername(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT email FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qWarning() << "Error: failed to get email:" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        return query.value(0).toString();
    }
    return QString(); // Not found
}

bool DatabaseManager::addIncident(const QString &title, const QString &description, const QString &imagePath, const QString &username, const QString &email)
{
    QSqlQuery query;
    query.prepare("INSERT INTO incidents (title, description, image_path, username, email) "
                  "VALUES (:title, :description, :image_path, :username, :email)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":image_path", imagePath);
    query.bindValue(":username", username);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qWarning() << "Error: failed to add incident:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Incident> DatabaseManager::getAllIncidents()
{
    QList<Incident> incidents;
    QSqlQuery query("SELECT id, title, description, image_path, username, email, timestamp "
                    "FROM incidents ORDER BY timestamp DESC"); // Show newest first

    if (!query.exec()) {
        qWarning() << "Error: failed to get incidents:" << query.lastError().text();
        return incidents;
    }

    while (query.next()) {
        Incident incident;
        incident.id = query.value(0).toInt();
        incident.title = query.value(1).toString();
        incident.description = query.value(2).toString();
        incident.imagePath = query.value(3).toString();
        incident.username = query.value(4).toString();
        incident.email = query.value(5).toString();
        incident.timestamp = query.value(6).toDateTime();
        incidents.append(incident);
    }
    return incidents;
}
// --- END NEW ---
