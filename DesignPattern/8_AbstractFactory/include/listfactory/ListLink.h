#ifndef LISTFACTORY_LISTLINK_H
#define LISTFACTORY_LISTLINK_H

#include "factory/Link.h"

namespace listfactory
{
    class ListLink : public factory::Link
    {
    public:
        ListLink(std::string caption, std::string url);
        std::string makeHTML() const override;
    };
}

#endif /* LISTFACTORY_LISTLINK_H */
