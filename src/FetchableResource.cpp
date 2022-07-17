
#include "qtpexels/FetchableResource.h"
#include <QNetworkReply>
#include <QJsonDocument>

qtpexels::FetchableResource::FetchableResource(QObject* parent)
    : QObject(parent)
{
}

void qtpexels::FetchableResource::fetch()
{
    emit fetchScheduled();
}

QString qtpexels::FetchableResource::error() const
{
    return _errorMessage;
}

void qtpexels::FetchableResource::setError(const QString& err)
{
    _errorMessage = err;
}

void qtpexels::FetchableResource::onNetworkReplyReceived()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NetworkError::NoError) {
        QByteArray body = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(body);

        if (processJSON(jsonDocument.object())) {
            emit finished();
        } else {
            setError(QString("Error processing JSON : %1").arg(reply->url().toString()));
            emit errorOccured();
        }
    }

    reply->deleteLater();
}

void qtpexels::FetchableResource::onNetworkReplyError(int errCode)
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    setError(reply->errorString());
    reply->deleteLater();
    emit errorOccured();
}
