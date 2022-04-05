#ifndef LISTFACTORY_LISTFACTORY_H
#define LISTFACTORY_LISTFACTORY_H

#include "factory/Factory.h"

namespace listfactory
{
    class ListFactory : public factory::Factory
    {
    public:
        std::unique_ptr<factory::Link> createLink(std::string caption, std::string url) override;
        std::unique_ptr<factory::Page> createPage(std::string title, std::string author) override;
        std::unique_ptr<factory::Tray> createTray(std::string caption) override;
    };
}

#endif /* LISTFACTORY_LISTFACTORY_H */
