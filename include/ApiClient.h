#pragma once
#include "qtpexels_global.h"

#include <QNetworkAccessManager>

namespace qtpexels {
static const QString PEXELS_URL = "https://api.pexels.com/v1";
// Photos
static const QString PEXELS_CURATED_PHOTOS_URL = QString("%1/curated").arg(PEXELS_URL);
static const QString PEXELS_SEARCH_PHOTOS_URL = QString("%1/search").arg(PEXELS_URL);
static const QString PEXELS_PHOTO_URL = QString("%1/photos").arg(PEXELS_URL);
// Videos
static const QString PEXELS_POPULAR_VIDEOS_URL = QString("%1/videos/popular").arg(PEXELS_URL);
static const QString PEXELS_SEARCH_VIDEOS_URL = QString("%1/videos/search").arg(PEXELS_URL);
static const QString PEXELS_VIDEO_URL = QString("%1/videos/videos").arg(PEXELS_URL);

class Photo;
class Video;
class PhotosPage;
class VideosPage;
class FetchableResource;

enum class Size {
    LARGE,
    MEDIUM,
    SMALL,
    UNDEFINED
};

enum class Orientation {
    LANDSCAPE,
    PORTRAIT,
    SQUARE,
    UNDEFINED
};

struct PhotoQueryParams {
    Orientation orientation = Orientation::UNDEFINED;
    Size size = Size::UNDEFINED;
    QString color;
    QString locale;
};

struct VideoQueryParams {
    Orientation orientation = Orientation::UNDEFINED;
    Size size = Size::UNDEFINED;
    QString locale;
};

struct VideoPopularQueryParams {
    int min_width = -1; // in pixels, -1 == undefined
    int min_height = -1; // in pixels, -1 == undefined
    int min_duration = -1; // duration in seconds, -1 == undefined
    int max_duration = -1; // duration in seconds, -1 == undefined
};

struct UserInfo {
    int id;
    QString name;
    QString webUrl;
};

struct RequestStatistics {
    uint limit = 0; // max request per month
    uint remaining = 0; // number of remaining requests per month
    unsigned long long resetTimestamp = 0; // unix timestamp when the statistics are reset
    QDateTime resetDateTime;
};

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

    const RequestStatistics& requestStatistics() const;

    ////////////
    // Photos //
    ////////////

    PhotosPage* queryCurratedPhotos(uint page = 1, uint itemsPerPage = 15) const;

    PhotosPage* queryPhotos(const QString& queryTerm, int page = 1, int itemsPerPage = 15) const;
    PhotosPage* queryPhotos(const QString& queryTerm, const PhotoQueryParams& queryParams, int page = 1, int itemsPerPage = 15) const;

    Photo* queryPhoto(int id) const;

    ////////////
    // Videos //
    ////////////

    VideosPage* queryPopularVideos(uint page = 1, uint itemsPerPage = 15) const;
    VideosPage* queryPopularVideos(const VideoPopularQueryParams& popularQueryParams, uint page = 1, uint itemsPerPage = 15) const;

    VideosPage* queryVideos(const QString& queryTerm, int page = 1, int itemsPerPage = 15) const;
    VideosPage* queryVideos(const QString& queryTerm, const VideoQueryParams& queryParams, int page = 1, int itemsPerPage = 15) const;

    Video* queryVideo(int id) const;

    /////////////////
    // Collections //
    /////////////////

    // TODO: implement the collections api

private:
    void fetchResource(const QUrl& url, FetchableResource* fetchableResource) const;
    void processRequestStatistics(QNetworkReply* reply) const;

private:
    QString _apiKey;
    QNetworkAccessManager* _networkAccessManager = nullptr;
    mutable RequestStatistics _requestStatistics;
};
}
