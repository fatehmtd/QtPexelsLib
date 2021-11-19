#pragma once
#include "Photo.h"
#include "ResultsPage.h"
#include <QList>

namespace qtpexels {
class QTPEXELS_EXPORT PhotosPage : public ResultsPage {
public:
    PhotosPage() = delete;
    Q_DISABLE_COPY_MOVE(PhotosPage);
    explicit PhotosPage(ApiClient* apiClient);

    virtual bool processJSON(const QJsonObject& jsonObject) override;

    QList<Photo*> photos() const;

private:
    QList<Photo*> _photos;
};
}
