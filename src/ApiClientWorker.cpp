#include "../include/ApiClientWorker.h"
#include "../include/PhotosPage.h"
#include "../include/VideosPage.h"
#include <QDateTime>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include <QJsonDocument>


using namespace qtpexels;

ApiClientWorker::ApiClientWorker(QString apiKey, QObject *parent) : QObject(parent), _apiKey(apiKey)
{
    _networkAccessManager = new QNetworkAccessManager(this);
}

qtpexels::RequestStatistics qtpexels::ApiClientWorker::requestStatistics() const
{
    return _requestStatistics;
}

void qtpexels::ApiClientWorker::queryCuratedPhotos(PhotosPage* fetchableResource,uint page, uint itemsPerPage)
{
    QString url = QString("%1?page=%2&per_page=%3").arg(PEXELS_CURATED_PHOTOS_URL).arg(page).arg(itemsPerPage);

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryPhotos(PhotosPage* fetchableResource,const QString& queryTerm, int page, int itemsPerPage)
{
    PhotoQueryParams queryParams;
    queryPhotos(fetchableResource, queryTerm, queryParams, page, itemsPerPage);
}

void qtpexels::ApiClientWorker::queryPhotos(PhotosPage* fetchableResource,const QString& queryTerm, const PhotoQueryParams& queryParams, int page, int itemsPerPage)
{
    QString url = QString("%1?query=%2&page=%3&per_page=%4").arg(PEXELS_SEARCH_PHOTOS_URL).arg(queryTerm).arg(page).arg(itemsPerPage);

    // process the size param
    QString sizeParam;
    switch (queryParams.size) {
    case Size::LARGE:
        sizeParam = "size=large";
        break;
    case Size::MEDIUM:
        sizeParam = "size=medium";
        break;
    case Size::SMALL:
        sizeParam = "size=small";
        break;
    default:
        sizeParam = "";
        break;
    }

    if (!sizeParam.isEmpty()) {
        url = QString("%1&%2").arg(url, sizeParam);
    }

    // process the orientation param
    QString orientationParam;
    switch (queryParams.orientation) {
    case Orientation::LANDSCAPE:
        orientationParam = "orientation=landscape";
        break;
    case Orientation::PORTRAIT:
        orientationParam = "orientation=portrait";
        break;
    case Orientation::SQUARE:
        orientationParam = "orientation=square";
        break;
    default:
        orientationParam = "";
        break;
    }

    if (!orientationParam.isEmpty()) {
        url = QString("%1&%2").arg(url, orientationParam);
    }

    if (!queryParams.color.isEmpty()) {
        url = QString("%1&color=%2").arg(url, queryParams.color);
    }

    if (!queryParams.locale.isEmpty()) {
        url = QString("%1&locale=%2").arg(url, queryParams.locale);
    }

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryPhoto(Photo* fetchableResource,int id)
{
    QString url = QString("%1/%2").arg(PEXELS_PHOTO_URL, id);

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryPopularVideos(VideosPage* fetchableResource,uint page, uint itemsPerPage)
{
    QString url = QString("%1?page=%2&per_page=%3").arg(PEXELS_POPULAR_VIDEOS_URL).arg(page).arg(itemsPerPage);

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryPopularVideos(VideosPage* fetchableResource, const VideoPopularQueryParams& popularQueryParams, uint page, uint itemsPerPage)
{
    QString url = QString("%1?page=%2&per_page=%3").arg(PEXELS_POPULAR_VIDEOS_URL).arg(page).arg(itemsPerPage);

    if (popularQueryParams.min_duration > -1) {
        url = QString("%1&min_duration=%2").arg(url, popularQueryParams.min_duration);
    }

    if (popularQueryParams.max_duration > -1) {
        url = QString("%1&max_duration=%2").arg(url, popularQueryParams.max_duration);
    }

    if (popularQueryParams.min_height > -1) {
        url = QString("%1&min_height=%2").arg(url, popularQueryParams.min_height);
    }

    if (popularQueryParams.min_width > -1) {
        url = QString("%1&min_width=%2").arg(url, popularQueryParams.min_width);
    }

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryVideos(VideosPage* fetchableResource, const QString& queryTerm, int page, int itemsPerPage)
{
    VideoQueryParams queryParams;
    queryVideos(fetchableResource, queryTerm, queryParams, page, itemsPerPage);
}

void qtpexels::ApiClientWorker::queryVideos(VideosPage* fetchableResource, const QString& queryTerm, const VideoQueryParams& queryParams, int page, int itemsPerPage)
{
    QString url = QString("%1?query=%2&page=%3&per_page=%4").arg(PEXELS_SEARCH_VIDEOS_URL).arg(queryTerm).arg(page).arg(itemsPerPage);

    // process the size param
    QString sizeParam;
    switch (queryParams.size) {
    case Size::LARGE:
        sizeParam = "size=large";
        break;
    case Size::MEDIUM:
        sizeParam = "size=medium";
        break;
    case Size::SMALL:
        sizeParam = "size=small";
        break;
    default:
        sizeParam = "";
        break;
    }

    if (!sizeParam.isEmpty()) {
        url = QString("%1&%2").arg(url, sizeParam);
    }

    // process the orientation param
    QString orientationParam;
    switch (queryParams.orientation) {
    case Orientation::LANDSCAPE:
        orientationParam = "orientation=landscape";
        break;
    case Orientation::PORTRAIT:
        orientationParam = "orientation=portrait";
        break;
    case Orientation::SQUARE:
        orientationParam = "orientation=square";
        break;
    default:
        orientationParam = "";
        break;
    }

    if (!orientationParam.isEmpty()) {
        url = QString("%1&%2").arg(url, orientationParam);
    }

    if (!queryParams.locale.isEmpty()) {
        url = QString("%1&locale=%2").arg(url, queryParams.locale);
    }

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::queryVideo(Video* fetchableResource, int id)
{
    QString url = QString("%1/%2").arg(PEXELS_VIDEO_URL, id);

    connect(fetchableResource, &FetchableResource::fetchScheduled, this, [=](){
        onFetchResourceRequested(url, fetchableResource);
    });
}

void qtpexels::ApiClientWorker::onFetchResourceRequested(const QUrl& url, FetchableResource* fetchableResource)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), _apiKey.toUtf8()); // send the api key in the Authorization header

    QNetworkReply* reply = _networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, fetchableResource, &FetchableResource::onNetworkReplyReceived);
    connect(reply, &QNetworkReply::finished, this, &ApiClientWorker::processRequestStatistics);
    connect(reply, &QNetworkReply::errorOccurred, fetchableResource, &FetchableResource::onNetworkReplyError);
}

void qtpexels::ApiClientWorker::processRequestStatistics()
{
    QMutexLocker locker(&_requestStatisticsMutex);
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NetworkError::NoError) {
        _requestStatistics.limit = reply->rawHeader("X-RateLimit-Limit").toUInt();
        _requestStatistics.remaining = reply->rawHeader("X-RateLimit-Remaining").toUInt();
        _requestStatistics.resetTimestamp = reply->rawHeader("X-RateLimit-Reset").toULongLong();
        _requestStatistics.resetDateTime.setSecsSinceEpoch(_requestStatistics.resetTimestamp);
    }
}
