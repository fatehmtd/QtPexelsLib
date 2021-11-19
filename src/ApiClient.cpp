#include "../include/ApiClient.h"
#include "../include/PhotosPage.h"
#include "../include/VideosPage.h"
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

qtpexels::ApiClient::ApiClient(const QString& apiKey, QObject* parent)
    : QObject(parent)
    , _apiKey(apiKey)
{
    Q_ASSERT(!apiKey.isEmpty());
    _networkAccessManager = new QNetworkAccessManager(this);
}

qtpexels::ApiClient::~ApiClient()
{
}

const qtpexels::RequestStatistics& qtpexels::ApiClient::requestStatistics() const
{
    return _requestStatistics;
}

qtpexels::PhotosPage* qtpexels::ApiClient::queryCurratedPhotos(uint page, uint itemsPerPage) const
{
    QString url = QString("%1?page=%2&per_page=%3").arg(PEXELS_CURATED_PHOTOS_URL).arg(page).arg(itemsPerPage);

    PhotosPage* resultsPage = new PhotosPage(const_cast<ApiClient*>(this));
    fetchResource(url, resultsPage);

    return resultsPage;
}

qtpexels::PhotosPage* qtpexels::ApiClient::queryPhotos(const QString& queryTerm, int page, int itemsPerPage) const
{
    PhotoQueryParams queryParams;
    return queryPhotos(queryTerm, queryParams, page, itemsPerPage);
}

qtpexels::PhotosPage* qtpexels::ApiClient::queryPhotos(const QString& queryTerm, const PhotoQueryParams& queryParams, int page, int itemsPerPage) const
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

    PhotosPage* resultsPage = new PhotosPage(const_cast<ApiClient*>(this));
    fetchResource(url, resultsPage);

    return resultsPage;
}

qtpexels::Photo* qtpexels::ApiClient::queryPhoto(int id) const
{
    QString url = QString("%1/%2").arg(PEXELS_PHOTO_URL, id);

    Photo* photo = new Photo(const_cast<ApiClient*>(this));
    fetchResource(url, photo);

    return photo;
}

qtpexels::VideosPage* qtpexels::ApiClient::queryPopularVideos(uint page, uint itemsPerPage) const
{
    QString url = QString("%1?page=%2&per_page=%3").arg(PEXELS_POPULAR_VIDEOS_URL).arg(page).arg(itemsPerPage);

    VideosPage* resultsPage = new VideosPage(const_cast<ApiClient*>(this));
    fetchResource(url, resultsPage);

    return resultsPage;
}

qtpexels::VideosPage* qtpexels::ApiClient::queryPopularVideos(const VideoPopularQueryParams& popularQueryParams, uint page, uint itemsPerPage) const
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

    VideosPage* resultsPage = new VideosPage(const_cast<ApiClient*>(this));
    fetchResource(url, resultsPage);

    return resultsPage;
}

qtpexels::VideosPage* qtpexels::ApiClient::queryVideos(const QString& queryTerm, int page, int itemsPerPage) const
{
    VideoQueryParams queryParams;
    return queryVideos(queryTerm, queryParams, page, itemsPerPage);
}

qtpexels::VideosPage* qtpexels::ApiClient::queryVideos(const QString& queryTerm, const VideoQueryParams& queryParams, int page, int itemsPerPage) const
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

    VideosPage* resultsPage = new VideosPage(const_cast<ApiClient*>(this));
    fetchResource(url, resultsPage);

    return resultsPage;
}

qtpexels::Video* qtpexels::ApiClient::queryVideo(int id) const
{
    QString url = QString("%1/%2").arg(PEXELS_VIDEO_URL, id);
    Video* video = new Video(const_cast<ApiClient*>(this));
    fetchResource(url, video);
    return video;
}

void qtpexels::ApiClient::fetchResource(const QUrl& url, FetchableResource* fetchableResource) const
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), _apiKey.toUtf8()); // send the api key in the Authorization header

    QNetworkReply* reply = _networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NetworkError::NoError) {
            processRequestStatistics(reply);
            QByteArray body = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(body);

            if (fetchableResource->processJSON(jsonDocument.object())) {
                emit fetchableResource->finished();
            } else {
                fetchableResource->setError(
                    QString("Error processing JSON : %1").arg(url.toString()));
                emit fetchableResource->errorOccured();
            }
        }

        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [=](QNetworkReply::NetworkError err) {
        fetchableResource->setError(reply->errorString());
        emit fetchableResource->errorOccured();
        reply->deleteLater();
    });
}

void qtpexels::ApiClient::processRequestStatistics(QNetworkReply* reply) const
{
    //Note : possible racing condition
    _requestStatistics.limit = reply->rawHeader("X-RateLimit-Limit").toUInt();
    _requestStatistics.remaining = reply->rawHeader("X-RateLimit-Remaining").toUInt();
    _requestStatistics.resetTimestamp = reply->rawHeader("X-RateLimit-Reset").toULongLong();
    _requestStatistics.resetDateTime.setSecsSinceEpoch(_requestStatistics.resetTimestamp);
}
