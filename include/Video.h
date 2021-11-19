#pragma once
#include "FetchableResource.h"

namespace qtpexels {
struct VideoFile {
    int id;
    enum Quality {
        SD,
        HD
    } quality;
    QString fileType;
    int width, height;
    QString link;
};

struct VideoImagePreview {
    int id;
    QString previewImageUrl;
    int nr; // misc
};

class QTPEXELS_EXPORT Video : public FetchableResource {
public:
    Video() = delete;
    Q_DISABLE_COPY_MOVE(Video);
    explicit Video(ApiClient* apiClient);

    int width() const;
    int height() const;
    int id() const;
    const QString& webUrl() const;
    const QString& previewImageUrl() const;
    int duration() const;
    bool processJSON(const QJsonObject& jsonObject);
    const UserInfo& userInfo() const;
    const QList<VideoFile>& videoFiles() const;
    const QList<VideoImagePreview>& previews() const;

private:
    int _width, _height;
    int _id;
    QString _webUrl, _previewImageUrl;
    int _duration;

    QList<VideoFile> _videos;
    QList<VideoImagePreview> _previews;
    UserInfo _userInfo;
};
}
