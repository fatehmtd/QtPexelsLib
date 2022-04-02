#include "../include/ApiClient.h"
#include "../include/PhotosPage.h"
#include "../include/VideosPage.h"
#include <QCoreApplication>

void logPhotoInfo(qtpexels::Photo* photo)
{
    qDebug() << QString("Photographer : %1, Dimensions : [%2x%3], avg_color : %5, url : %4")
                    .arg(photo->userInfo().name)
                    .arg(photo->width())
                    .arg(photo->height())
                    .arg(photo->webUrl())
                    .arg(photo->avgColorHex());

    qDebug() << QString("  - ORIGINAL url : %1").arg(photo->srcUrl(qtpexels::Photo::ORIGINAL));
    qDebug() << QString("  - TINY url : %1").arg(photo->srcUrl(qtpexels::Photo::TINY));
}

void logVideoInfo(qtpexels::Video* video)
{
    qDebug() << QString("Videographer : %1, Dimensions : [%2x%3], duration : %5 sec, url : %4")
                    .arg(video->userInfo().name)
                    .arg(video->width())
                    .arg(video->height())
                    .arg(video->webUrl())
                    .arg(video->duration());
    const auto& previews = video->previews();
    std::for_each(previews.begin(), previews.end(), [](const qtpexels::VideoImagePreview& preview) {
        qDebug() << preview.previewImageUrl;
    });
}

void logInfo(qtpexels::ResultsPage* resultsPage, QString title)
{
    qDebug() << title
             << QString("Total items : %2, Total pages : %3, Items "
                        "per page : %4, Next page available : %1")
                    .arg(resultsPage->hasNext() ? "True" : "False")
                    .arg(resultsPage->totalItems())
                    .arg(resultsPage->totalPages())
                    .arg(resultsPage->itemsPerPage());

    auto photosPage = dynamic_cast<qtpexels::PhotosPage*>(resultsPage);
    if (photosPage != nullptr) {
        const auto& photos = photosPage->photos();
        std::for_each(photos.begin(), photos.end(), &logPhotoInfo);
    } else {
        auto videosPage = dynamic_cast<qtpexels::VideosPage*>(resultsPage);
        const auto& videos = videosPage->videos();
        std::for_each(videos.begin(), videos.end(), &logVideoInfo);
    }
    qDebug() << "----------------------------------";
}

void logRequestStats(qtpexels::ApiClient* apiClient)
{
    auto stats = apiClient->requestStatistics();
    qDebug() << "API USAGE STATISTICS : " << QString("%1/%2, Limits reset date : %3").arg(stats.remaining).arg(stats.limit).arg(stats.resetDateTime.toString());
}

void connectLogging(qtpexels::ResultsPage* resultsPage, QString title)
{
    QObject::connect(resultsPage, &qtpexels::ResultsPage::finished, resultsPage, [=]() {
        logInfo(resultsPage, title);
        //logRequestStats(resultsPage->apiClient());
    });

    QObject::connect(resultsPage, &qtpexels::ResultsPage::errorOccured, resultsPage, [=]() {
        qDebug() << "*** Error : " << title << " message : " << resultsPage->error();
        //logRequestStats(resultsPage->apiClient());
    });
}

void queryCuratedPhotos(qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryCuratedPhotos(1, 10);
    connectLogging(resultsPage, "** Query Curated Photos : ");

    resultsPage->fetch();
}

void queryPopularVideos(qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryPopularVideos(1, 10);
    connectLogging(resultsPage, "** Query popular videos : ");
    resultsPage->fetch();
}

void queryPhotosWithParams(qtpexels::ApiClient& client)
{
    qtpexels::PhotoQueryParams queryParams;
    //queryParams.orientation = qtpexels::Orienation::LANDSCAPE;
    queryParams.size = qtpexels::Size::LARGE;

    auto resultsPage = client.queryPhotos("space", // keyword
        queryParams, // query params, ie: size and orientation
        1, // page index starting from 1
        10); // number of items per page

    connectLogging(resultsPage, "** Query Photos with params : ");
    resultsPage->fetch();
}

void queryVideosWithParams(qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryVideos("green", 1, 10); // search videos with the "green" keyword

    connectLogging(resultsPage, "** Query Videos with params : ");
    resultsPage->fetch();
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    const QString apiKey = "563492ad6f91700001000001d0fac28cfd6b48fe9efd5a2b1bb92e08";

    qtpexels::ApiClient client(apiKey);

    queryCuratedPhotos(client);
    queryPopularVideos(client);

    queryPhotosWithParams(client);
    queryVideosWithParams(client);

    return a.exec();
}
