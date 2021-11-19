#include "../include/VideosPage.h"
#include <QJsonArray>

qtpexels::VideosPage::VideosPage(ApiClient* apiClient)
    : ResultsPage(apiClient)
{
}

bool qtpexels::VideosPage::processJSON(const QJsonObject& jsonObject)
{
    if (!ResultsPage::processJSON(jsonObject))
        return false;

    const auto& jsonVideosArray = jsonObject["videos"].toArray();

    std::for_each(jsonVideosArray.begin(), jsonVideosArray.end(), [=](const QJsonValue& jsonValue) {
        const auto& jsonVideo = jsonValue.toObject();
        Video* video = new Video(apiClient());
        video->processJSON(jsonVideo);
        _videos << video;
    });

    return true;
}

QList<qtpexels::Video*> qtpexels::VideosPage::videos() const
{
    return _videos;
}
