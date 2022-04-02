#pragma once
#include "ApiClientWorker.h"

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

    PhotosPage* queryCuratedPhotos(uint page = 1, uint itemsPerPage = 15);

    PhotosPage* queryPhotos(const QString& queryTerm, int page = 1, int itemsPerPage = 15);
    PhotosPage* queryPhotos(const QString& queryTerm, const PhotoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

    Photo* queryPhoto(int id);

    ////////////
    // Videos //
    ////////////

    VideosPage* queryPopularVideos(uint page = 1, uint itemsPerPage = 15);
    VideosPage* queryPopularVideos(const VideoPopularQueryParams& popularQueryParams, uint page = 1, uint itemsPerPage = 15);

    VideosPage* queryVideos(const QString& queryTerm, int page = 1, int itemsPerPage = 15);
    VideosPage* queryVideos(const QString& queryTerm, const VideoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

    Video* queryVideo(int id);

    /////////////////
    // Collections //
    /////////////////
    // TODO: implement the collections api

private:
    QScopedPointer<ApiClientWorker> _apiClientWorker;
};
}
