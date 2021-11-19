#include "../include/FetchableResource.h"

qtpexels::FetchableResource::FetchableResource(ApiClient* apiClient)
    : QObject(apiClient)
{
}

QString qtpexels::FetchableResource::error() const
{
    return _errorMessage;
}

qtpexels::ApiClient* qtpexels::FetchableResource::apiClient() const
{
    return dynamic_cast<ApiClient*>(parent());
}

void qtpexels::FetchableResource::setError(const QString& err)
{
    _errorMessage = err;
}
