
#include "qtpexels/Collection.h"

qtpexels::Collection::Collection(QObject* parent)
    : FetchableResource(parent)
{
}

bool qtpexels::Collection::processJSON(const QJsonObject& jsonObject)
{
    _id = jsonObject["id"].toString();
    _title = jsonObject["title"].toString();
    _description = jsonObject["description"].toString();
    _private = jsonObject["private"].toBool();
    _mediaCount = jsonObject["media_count"].toInt();
    _photosCount = jsonObject["photos_count"].toInt();
    _videosCount = jsonObject["videos_count"].toInt();
    return true;
}

const QString& qtpexels::Collection::id() const
{
    return _id;
}

const QString& qtpexels::Collection::title() const
{
    return _title;
}

const QString& qtpexels::Collection::description() const
{
    return _description;
}

bool qtpexels::Collection::isPrivate() const
{
    return _private;
}

int qtpexels::Collection::mediaCount() const
{
    return _mediaCount;
}

int qtpexels::Collection::photosCount() const
{
    return _photosCount;
}

int qtpexels::Collection::videosCount() const
{
    return _videosCount;
}

const QList<qtpexels::Photo*>& qtpexels::Collection::photos() const
{
    return _photos;
}

const QList<qtpexels::Video*>& qtpexels::Collection::videos() const
{
    return _videos;
}
