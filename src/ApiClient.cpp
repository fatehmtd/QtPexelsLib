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

QSharedPointer<qtpexels::PhotosPage> qtpexels::ApiClient::queryCuratedPhotos(uint page, uint itemsPerPage)
{
    QSharedPointer<qtpexels::PhotosPage> fetchableResource(new PhotosPage(this));
    _apiClientWorker->queryCuratedPhotos(fetchableResource.get(), page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::PhotosPage> qtpexels::ApiClient::queryPhotos(const QString &queryTerm, int page, int itemsPerPage)
{
    QSharedPointer<qtpexels::PhotosPage> fetchableResource(new PhotosPage(this));
    _apiClientWorker->queryPhotos(fetchableResource.get(), queryTerm, page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::PhotosPage> qtpexels::ApiClient::queryPhotos(const QString &queryTerm, const PhotoQueryParams &queryParams, int page, int itemsPerPage)
{
    QSharedPointer<qtpexels::PhotosPage> fetchableResource(new PhotosPage(this));
    _apiClientWorker->queryPhotos(fetchableResource.get(), queryTerm, queryParams, page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::Photo> qtpexels::ApiClient::queryPhoto(int id)
{
    QSharedPointer<qtpexels::Photo> fetchableResource(new Photo(this));
    _apiClientWorker->queryPhoto(fetchableResource.get(), id);
    return fetchableResource;
}

QSharedPointer<qtpexels::VideosPage> qtpexels::ApiClient::queryPopularVideos(uint page, uint itemsPerPage)
{
    QSharedPointer<qtpexels::VideosPage> fetchableResource(new VideosPage(this));
    _apiClientWorker->queryPopularVideos(fetchableResource.get(), page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::VideosPage> qtpexels::ApiClient::queryPopularVideos(const VideoPopularQueryParams &popularQueryParams, uint page, uint itemsPerPage)
{
    QSharedPointer<qtpexels::VideosPage> fetchableResource(new VideosPage(this));
    _apiClientWorker->queryPopularVideos(fetchableResource.get(), popularQueryParams, page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::VideosPage> qtpexels::ApiClient::queryVideos(const QString &queryTerm, int page, int itemsPerPage)
{
    QSharedPointer<qtpexels::VideosPage> fetchableResource(new VideosPage(this));
    _apiClientWorker->queryVideos(fetchableResource.get(), queryTerm, page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::VideosPage> qtpexels::ApiClient::queryVideos(const QString &queryTerm, const VideoQueryParams &queryParams, int page, int itemsPerPage)
{
    QSharedPointer<qtpexels::VideosPage> fetchableResource(new VideosPage(this));
    _apiClientWorker->queryVideos(fetchableResource.get(), queryTerm, queryParams, page, itemsPerPage);
    return fetchableResource;
}

QSharedPointer<qtpexels::Video> qtpexels::ApiClient::queryVideo(int id)
{
    QSharedPointer<qtpexels::Video> fetchableResource(new Video(this));
    _apiClientWorker->queryVideo(fetchableResource.get(), id);
    return fetchableResource;
}

