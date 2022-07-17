
#include "qtpexels/Video.h"
#include <QJsonArray>

qtpexels::Video::Video(QObject* parent)
    : FetchableResource(parent)
{
}

int qtpexels::Video::width() const
{
    return _width;
}

int qtpexels::Video::height() const
{
    return _height;
}

int qtpexels::Video::id() const
{
    return _id;
}

const QString& qtpexels::Video::webUrl() const
{
    return _webUrl;
}

const QString& qtpexels::Video::previewImageUrl() const
{
    return _previewImageUrl;
}

int qtpexels::Video::duration() const
{
    return _duration;
}

bool qtpexels::Video::processJSON(const QJsonObject& jsonObject)
{
    _width = jsonObject["width"].toInt();
    _height = jsonObject["height"].toInt();
    _id = jsonObject["id"].toInt();

    const auto& jsonUser = jsonObject["user"].toObject();
    _userInfo.name = jsonUser["name"].toString();
    _userInfo.id = jsonUser["id"].toInt();
    _userInfo.webUrl = jsonUser["url"].toString();

    _webUrl = jsonObject["url"].toString();
    _duration = jsonObject["duration"].toInt();

    const auto& jsonVideosArray = jsonObject["video_files"].toArray();

    std::for_each(jsonVideosArray.begin(), jsonVideosArray.end(), [=](const QJsonValue& jsonValue) {
        const auto& jsonVideo = jsonValue.toObject();
        VideoFile videoFile;
        videoFile.width = jsonVideo["width"].toInt();
        videoFile.height = jsonVideo["height"].toInt();
        videoFile.fileType = jsonVideo["file_type"].toString();
        videoFile.link = jsonVideo["link"].toString();
        videoFile.quality = (jsonVideo["quality"].toString() == "sd") ? VideoFile::Quality::SD : VideoFile::Quality::HD;
        _videos.append(videoFile);
    });

    const auto& jsonVideoPreviewsArray = jsonObject["video_pictures"].toArray();
    std::for_each(jsonVideoPreviewsArray.begin(), jsonVideoPreviewsArray.end(), [=](const QJsonValue& jsonValue) {
        const auto& jsonVideoPreviewImage = jsonValue.toObject();
        VideoImagePreview imagePreview;
        imagePreview.id = jsonVideoPreviewImage["id"].toInt();
        imagePreview.nr = jsonVideoPreviewImage["nr"].toInt();
        imagePreview.previewImageUrl = jsonVideoPreviewImage["picture"].toString();
        _previews.append(imagePreview);
    });

    return true;
}

const qtpexels::UserInfo& qtpexels::Video::userInfo() const
{
    return _userInfo;
}

const QList<qtpexels::VideoFile>& qtpexels::Video::videoFiles() const
{
    return _videos;
}

const QList<qtpexels::VideoImagePreview>& qtpexels::Video::previews() const
{
    return _previews;
}
