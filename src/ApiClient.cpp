#include "../include/ApiClient.h"
#include "../include/PhotosPage.h"
#include "../include/VideosPage.h"
#include <QThread>

qtpexels::ApiClient::ApiClient(const QString& apiKey, QObject* parent)
    : QObject(parent), _apiClientWorker(new ApiClientWorker(apiKey))
{
    Q_ASSERT(!apiKey.isEmpty());

    // Event processing thread
    QThread *thread = new QThread();
    connect(this, &QObject::destroyed, thread, &QObject::deleteLater);

    _apiClientWorker->moveToThread(thread);

    thread->start();
}

qtpexels::ApiClient::~ApiClient()
{
}

qtpexels::RequestStatistics qtpexels::ApiClient::requestStatistics() const
{
    return _apiClientWorker->requestStatistics();
}

qtpexels::PhotosPage *qtpexels::ApiClient::queryCuratedPhotos(uint page, uint itemsPerPage)
{
    PhotosPage *fetchableResource = new PhotosPage(this);
    _apiClientWorker->queryCuratedPhotos(fetchableResource, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::PhotosPage *qtpexels::ApiClient::queryPhotos(const QString &queryTerm, int page, int itemsPerPage)
{
    PhotosPage *fetchableResource = new PhotosPage(this);
    _apiClientWorker->queryPhotos(fetchableResource, queryTerm, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::PhotosPage *qtpexels::ApiClient::queryPhotos(const QString &queryTerm, const PhotoQueryParams &queryParams, int page, int itemsPerPage)
{
    PhotosPage *fetchableResource = new PhotosPage(this);
    _apiClientWorker->queryPhotos(fetchableResource, queryTerm, queryParams, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::Photo *qtpexels::ApiClient::queryPhoto(int id)
{
    Photo*fetchableResource = new Photo(this);
    _apiClientWorker->queryPhoto(fetchableResource, id);
    return fetchableResource;
}

qtpexels::VideosPage *qtpexels::ApiClient::queryPopularVideos(uint page, uint itemsPerPage)
{
    VideosPage *fetchableResource = new VideosPage(this);
    _apiClientWorker->queryPopularVideos(fetchableResource, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::VideosPage *qtpexels::ApiClient::queryPopularVideos(const VideoPopularQueryParams &popularQueryParams, uint page, uint itemsPerPage)
{
    VideosPage *fetchableResource = new VideosPage(this);
    _apiClientWorker->queryPopularVideos(fetchableResource, popularQueryParams, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::VideosPage *qtpexels::ApiClient::queryVideos(const QString &queryTerm, int page, int itemsPerPage)
{
    VideosPage *fetchableResource = new VideosPage(this);
    _apiClientWorker->queryVideos(fetchableResource, queryTerm, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::VideosPage *qtpexels::ApiClient::queryVideos(const QString &queryTerm, const VideoQueryParams &queryParams, int page, int itemsPerPage)
{
    VideosPage *fetchableResource = new VideosPage(this);
    _apiClientWorker->queryVideos(fetchableResource, queryTerm, queryParams, page, itemsPerPage);
    return fetchableResource;
}

qtpexels::Video *qtpexels::ApiClient::queryVideo(int id)
{
    Video *fetchableResource = new Video(this);
    _apiClientWorker->queryVideo(fetchableResource, id);
    return fetchableResource;
}

