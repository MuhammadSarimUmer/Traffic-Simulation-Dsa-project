#include "map_loader.h"
#include <QUrlQuery>
#include <QDebug>

MapLoader::MapLoader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MapLoader::onReplyFinished);
}

QString MapLoader::buildOverpassQuery(double minLat, double minLon, double maxLat, double maxLon)
{
    // [out:json];(way["highway"](bbox););(._;>;);out body;
    QString bbox = QString::number(minLat) + "," +
                   QString::number(minLon) + "," +
                   QString::number(maxLat) + "," +
                   QString::number(maxLon);

    return QString("[out:json];(way[\"highway\"](%1););(._;>;);out body;").arg(bbox);
}

void MapLoader::fetchMapData(double minLat, double minLon, double maxLat, double maxLon)
{
    QString query = buildOverpassQuery(minLat, minLon, maxLat, maxLon);

    QUrl url("https://overpass-api.de/api/interpreter");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("data", query);

    qDebug() << "Sending Overpass query...";
    manager->post(request, postData.query(QUrl::FullyEncoded).toUtf8());
}

void MapLoader::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "API data received successfully.";
        emit mapDataReady(reply->readAll());
    } else {
        qDebug() << "API Error:" << reply->errorString();
        emit mapLoadFailed(reply->errorString());
    }
    reply->deleteLater();
}
