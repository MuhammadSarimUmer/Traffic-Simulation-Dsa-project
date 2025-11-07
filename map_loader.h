#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>

class MapLoader : public QObject
{
    Q_OBJECT // <--- This is essential for signals

public:
    explicit MapLoader(QObject *parent = nullptr);
    void fetchMapData(double minLat, double minLon, double maxLat, double maxLon);

signals:
    void mapDataReady(const QByteArray& data);
    void mapLoadFailed(const QString& error);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *manager;
    QString buildOverpassQuery(double minLat, double minLon, double maxLat, double maxLon);
};

#endif // MAP_LOADER_H
