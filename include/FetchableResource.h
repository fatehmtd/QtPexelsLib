#pragma once

#include "ApiClient.h"
#include <QJsonObject>
#include <QString>

namespace qtpexels {
class QTPEXELS_EXPORT FetchableResource : public QObject {
    Q_OBJECT
public:
    FetchableResource() = delete;
    Q_DISABLE_COPY_MOVE(FetchableResource);
    FetchableResource(ApiClient* apiClient);
    virtual ~FetchableResource() {};

    virtual bool processJSON(const QJsonObject& jsonObject) = 0;

    QString error() const;

    ApiClient* apiClient() const;

    void setError(const QString& err);

signals:
    void finished();
    void errorOccured();

private:
    QString _errorMessage;
};
}
