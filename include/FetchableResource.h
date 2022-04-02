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
    explicit FetchableResource(QObject* parent);
    virtual ~FetchableResource() {};

    void fetch();

    QString error() const;

protected:
    void setError(const QString& err);
    virtual bool processJSON(const QJsonObject& jsonObject) = 0;

public slots:
    void onNetworkReplyReceived();
    void onNetworkReplyError(int errCode);

signals:
    void finished();
    void errorOccured();
    void fetchScheduled();

private:
    QString _errorMessage;
};
}
