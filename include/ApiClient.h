#pragma once
#include "ApiClientWorker.h"
#include <QSharedPointer>
namespace qtpexels {


/////////////////////////////////
/// \brief The ApiClient class
///
class QTPEXELS_EXPORT ApiClient : public QObject {
    Q_OBJECT
public:
    ApiClient() = delete;
    Q_DISABLE_COPY_MOVE(ApiClient);
    explicit ApiClient(const QString& apiKey, QObject* parent = nullptr);
    ~ApiClient();

    RequestStatistics requestStatistics() const;

    ////////////
    // Photos //
    ////////////

    QSharedPointer<PhotosPage> queryCuratedPhotos(uint page = 1, uint itemsPerPage = 15);

    QSharedPointer<PhotosPage> queryPhotos(const QString& queryTerm, int page = 1, int itemsPerPage = 15);
    QSharedPointer<PhotosPage> queryPhotos(const QString& queryTerm, const PhotoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

    QSharedPointer<Photo> queryPhoto(int id);

    ////////////
    // Videos //
    ////////////

    QSharedPointer<VideosPage> queryPopularVideos(uint page = 1, uint itemsPerPage = 15);
    QSharedPointer<VideosPage> queryPopularVideos(const VideoPopularQueryParams& popularQueryParams, uint page = 1, uint itemsPerPage = 15);

    QSharedPointer<VideosPage> queryVideos(const QString& queryTerm, int page = 1, int itemsPerPage = 15);
    QSharedPointer<VideosPage> queryVideos(const QString& queryTerm, const VideoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

    QSharedPointer<Video> queryVideo(int id);

    /////////////////
    // Collections //
    /////////////////
    // TODO: implement the collections api

private:
    QScopedPointer<ApiClientWorker> _apiClientWorker;
};
}
