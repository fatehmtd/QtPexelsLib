
#include "qtpexels/ResultsPage.h"

qtpexels::ResultsPage::ResultsPage(QObject* parent)
    : FetchableResource(parent)
{
    _pageIndex = 1;
    _itemsPerPage = 20;
    _totalItems = 0;
    _totalPages = 0;
    _hasNext = false;
}

uint qtpexels::ResultsPage::pageIndex() const
{
    return _pageIndex;
}

uint qtpexels::ResultsPage::itemsPerPage() const
{
    return _itemsPerPage;
}

uint qtpexels::ResultsPage::totalItems() const
{
    return _totalItems;
}

uint qtpexels::ResultsPage::totalPages() const
{
    return _totalPages;
}

bool qtpexels::ResultsPage::hasNext() const
{
    return _hasNext;
}

QString qtpexels::ResultsPage::lastError() const
{
    return _lastError;
}

bool qtpexels::ResultsPage::processJSON(const QJsonObject& jsonObject)
{
    _pageIndex = jsonObject["page"].toInt();
    _totalItems = jsonObject["total_results"].toInt();
    _itemsPerPage = jsonObject["per_page"].toInt();
    _hasNext = jsonObject.find("next_page") != jsonObject.end();

    if (_totalItems > 0) {
        _totalPages = _totalItems / _itemsPerPage + 1;
    } else {
        _totalPages = 0;
    }

    return true;
}
