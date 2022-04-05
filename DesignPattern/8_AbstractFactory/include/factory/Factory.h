#ifndef FACTORY_FACTORY_H
#define FACTORY_FACTORY_H

#include <string_view>
#include "Link.h"
#include "Page.h"
#include "Tray.h"

namespace factory
{
    class Factory
    {
    public:
        static Factory& GetFactory(std::string_view className);
        virtual std::unique_ptr<Link> createLink(std::string caption, std::string url) = 0;
        virtual std::unique_ptr<Page> createPage(std::string title, std::string author) = 0;
        virtual std::unique_ptr<Tray> createTray(std::string caption) = 0;
    };
}

#endif /* FACTORY_FACTORY_H */
