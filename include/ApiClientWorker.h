#pragma once

#include "qtpexels_global.h"
#include <QNetworkAccessManager>
#include <QMutexLocker>

namespace qtpexels {

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

    class ApiClientWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit ApiClientWorker(QString apiKey, QObject *parent=nullptr);

        RequestStatistics requestStatistics() const;

        ////////////
        // Photos //
        ////////////

        void queryCuratedPhotos(PhotosPage* fetchableResource, uint page = 1, uint itemsPerPage = 15);

        void queryPhotos(PhotosPage* fetchableResource,const QString& queryTerm, int page = 1, int itemsPerPage = 15);
        void queryPhotos(PhotosPage* fetchableResource,const QString& queryTerm, const PhotoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

        void queryPhoto(Photo* fetchableResource,int id);

        ////////////
        // Videos //
        ////////////

        void queryPopularVideos(VideosPage* fetchableResource,uint page = 1, uint itemsPerPage = 15);
        void queryPopularVideos(VideosPage* fetchableResource,const VideoPopularQueryParams& popularQueryParams, uint page = 1, uint itemsPerPage = 15);

        void queryVideos(VideosPage* fetchableResource,const QString& queryTerm, int page = 1, int itemsPerPage = 15);
        void queryVideos(VideosPage* fetchableResource,const QString& queryTerm, const VideoQueryParams& queryParams, int page = 1, int itemsPerPage = 15);

        void queryVideo(Video* fetchableResource,int id);

        /////////////////
        // Collections //
        /////////////////

    signals:
        void fetchResource(const QUrl& url, qtpexels::FetchableResource* fetchableResource);

    private:
        void onFetchResourceRequested(const QUrl& url, FetchableResource* fetchableResource);

    private slots:
        void processRequestStatistics();

    private:
        QMutex _requestStatisticsMutex;
        QString _apiKey;
        QNetworkAccessManager* _networkAccessManager = nullptr;
        mutable RequestStatistics _requestStatistics;

        // Api urls
        const QString PEXELS_URL = "https://api.pexels.com/v1";
        // Photos
        const QString PEXELS_CURATED_PHOTOS_URL = QString("%1/curated").arg(PEXELS_URL);
        const QString PEXELS_SEARCH_PHOTOS_URL = QString("%1/search").arg(PEXELS_URL);
        const QString PEXELS_PHOTO_URL = QString("%1/photos").arg(PEXELS_URL);
        // Videos
        const QString PEXELS_POPULAR_VIDEOS_URL = QString("%1/videos/popular").arg(PEXELS_URL);
        const QString PEXELS_SEARCH_VIDEOS_URL = QString("%1/videos/search").arg(PEXELS_URL);
        const QString PEXELS_VIDEO_URL = QString("%1/videos/videos").arg(PEXELS_URL);
    };

}

