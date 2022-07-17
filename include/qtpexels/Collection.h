#pragma once

#include "qtpexels/FetchableResource.h"
#include "Photo.h"
#include "Video.h"

namespace qtpexels {

class QTPEXELS_EXPORT Collection : public FetchableResource {
public:
    Collection() = delete;
    Q_DISABLE_COPY_MOVE(Collection);
    explicit Collection(QObject* parent);

    bool processJSON(const QJsonObject& jsonObject) override;

    const QString& id() const;
    const QString& title() const;
    const QString& description() const;
    bool isPrivate() const;
    int mediaCount() const;
    int photosCount() const;
    int videosCount() const;
    const QList<Photo*>& photos() const;
    const QList<Video*>& videos() const;

private:
    QString _id;
    QString _title;
    QString _description;
    bool _private;
    int _mediaCount;
    int _photosCount;
    int _videosCount;
    QList<Photo*> _photos;
    QList<Video*> _videos;
};

}
