#pragma once
#include "ResultsPage.h"
#include "Video.h"
#include <QList>

namespace qtpexels {
class QTPEXELS_EXPORT VideosPage : public ResultsPage {
public:
    VideosPage() = delete;
    Q_DISABLE_COPY_MOVE(VideosPage);
    explicit VideosPage(ApiClient* apiClient);

    virtual bool processJSON(const QJsonObject& jsonObject) override;

    QList<Video*> videos() const;

private:
    QList<Video*> _videos;
};
}
