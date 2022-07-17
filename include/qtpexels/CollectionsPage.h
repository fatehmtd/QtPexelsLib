#pragma once

#include "qtpexels/FetchableResource.h"

namespace qtpexels {

// TODO: implement the collections api logic

class CollectionsPage : public FetchableResource
{
public:
    CollectionsPage() = delete;
    Q_DISABLE_COPY_MOVE(CollectionsPage);
    explicit CollectionsPage(QObject* parent);
};
}
