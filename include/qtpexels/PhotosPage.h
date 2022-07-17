#pragma once

#include "qtpexels/Photo.h"
#include "qtpexels/ResultsPage.h"
#include <QList>

namespace qtpexels {
class QTPEXELS_EXPORT PhotosPage : public ResultsPage {
public:
    PhotosPage() = delete;
    Q_DISABLE_COPY_MOVE(PhotosPage);
    explicit PhotosPage(QObject* parent);

    virtual bool processJSON(const QJsonObject& jsonObject) override;

    QList<Photo*> photos() const;

private:
    QList<Photo*> _photos;
};
}
