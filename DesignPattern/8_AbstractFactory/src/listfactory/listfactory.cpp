#include "listfactory/ListFactory.h"

using namespace factory;
namespace listfactory
{
    std::unique_ptr<Link> ListFactory::createLink(std::string caption, std::string url)
    {
        return std::make_unique<Link>(std::move(caption), std::move(url));
    }

    std::unique_ptr<Page> ListFactory::createPage(std::string title, std::string author)
    {
        return std::make_unique<Page>(std::move(title), std::move(author));
    }

    std::unique_ptr<Tray> ListFactory::createTray(std::string caption)
    {
        return std::make_unique<Tray>(std::move(caption));
    }
}