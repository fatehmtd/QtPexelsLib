#include "../include/Photo.h"
#include <QDebug>
#include <QMap>

qtpexels::Photo::Photo(ApiClient* apiClient)
    : FetchableResource(apiClient)
{
}

QString qtpexels::Photo::webUrl() const
{
    return _webUrl;
}

QString qtpexels::Photo::srcUrl(PhotoSize photoSize) const
{
    return _srcUrls[(int)photoSize];
}

int qtpexels::Photo::width() const
{
    return _width;
}

int qtpexels::Photo::height() const
{
    return _height;
}

QString qtpexels::Photo::avgColorHex() const
{
    return _avgColorHex;
}

int qtpexels::Photo::id() const
{
    return _id;
}

const qtpexels::UserInfo& qtpexels::Photo::userInfo() const
{
    return _userInfo;
}

bool qtpexels::Photo::processJSON(const QJsonObject& jsonObject)
{
    _width = jsonObject["width"].toInt();
    _height = jsonObject["height"].toInt();
    _id = jsonObject["id"].toInt();
    _avgColorHex = jsonObject["avg_color"].toString();
    _userInfo.name = jsonObject["photographer"].toString();
    _userInfo.id = jsonObject["photographer_id"].toInt();
    _userInfo.webUrl = jsonObject["photographer_url"].toString();
    _webUrl = jsonObject["url"].toString();

    static QMap<QString, int> photoSizesMap {
        { "original", PhotoSize::ORIGINAL },
        { "large2x", PhotoSize::LARGE2X },
        { "large", PhotoSize::LARGE },
        { "medium", PhotoSize::MEDIUM },
        { "small", PhotoSize::SMALL },
        { "tiny", PhotoSize::TINY },
        { "portrait", PhotoSize::PORTRAIT },
        { "landscape", PhotoSize::LANDSCAPE }
    };

    const auto& keys = photoSizesMap.keys();
    std::for_each(keys.begin(), keys.end(), [=](const QString& key) {
        _srcUrls[photoSizesMap[key]] = jsonObject["src"].toObject()[key].toString();
    });

    return true;
}
