#include "../include/PhotosPage.h"
#include "../include/Photo.h"
#include <QJsonArray>
#include <QJsonObject>

qtpexels::PhotosPage::PhotosPage(QObject* parent)
    : ResultsPage(parent)
{
}

bool qtpexels::PhotosPage::processJSON(const QJsonObject& jsonObject)
{
    if (!ResultsPage::processJSON(jsonObject))
        return false;

    // parse photos
    const QJsonArray& jsonArray = jsonObject["photos"].toArray();

    std::for_each(jsonArray.begin(), jsonArray.end(), [=](const QJsonValue& jsonValue) {
        auto photo = new Photo(this);
        photo->processJSON(jsonValue.toObject());
        _photos << photo;
    });

    return true;
}

QList<qtpexels::Photo*> qtpexels::PhotosPage::photos() const
{
    return _photos;
}
