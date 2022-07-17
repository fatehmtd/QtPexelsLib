#pragma once

#include "qtpexels/FetchableResource.h"
#include <QObject>

namespace qtpexels {
class QTPEXELS_EXPORT Photo : public FetchableResource {
public:
    enum PhotoSize {
        ORIGINAL,
        LARGE2X,
        LARGE,
        MEDIUM,
        SMALL,
        PORTRAIT,
        LANDSCAPE,
        TINY,
        _COUNT
    };

    Photo() = delete;
    Q_DISABLE_COPY_MOVE(Photo);
    explicit Photo(QObject* parent);

    bool processJSON(const QJsonObject& jsonObject) override;

    QString webUrl() const;
    QString srcUrl(PhotoSize photoSize) const;

    int width() const;
    int height() const;

    QString avgColorHex() const;

    int id() const;

    const UserInfo& userInfo() const;

private:
    QString _webUrl;
    int _width, _height;
    int _id;
    QString _avgColorHex;
    QString _srcUrls[_COUNT];
    UserInfo _userInfo;
};
}
