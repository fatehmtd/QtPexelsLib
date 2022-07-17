#pragma once

#include "qtpexels/FetchableResource.h"

namespace qtpexels {
class QTPEXELS_EXPORT ResultsPage : public FetchableResource {
public:
    ResultsPage() = delete;
    Q_DISABLE_COPY_MOVE(ResultsPage);
    explicit ResultsPage(QObject* parent);

    uint pageIndex() const;
    uint itemsPerPage() const;
    uint totalItems() const;
    uint totalPages() const;
    bool hasNext() const;
    QString lastError() const;

    virtual bool processJSON(const QJsonObject& jsonObject) override;

private:
    uint _pageIndex;
    bool _hasNext;
    uint _itemsPerPage;
    uint _totalItems;
    uint _totalPages;
    QString _lastError;
};
}
