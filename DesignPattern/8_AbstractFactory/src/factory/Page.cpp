#include "factory/Page.h"
#include <iostream>

namespace factory
{
    Page::Page(std::string title, std::string author)
        : title(std::move(title))
        , author(std::move(author))
    {
    }

    void Page::add(std::unique_ptr<Item>&& item)
    {
        items.push_back(std::move(item));
    }

    void Page::output() const
    {
        std::cout << makeHTML() << '\n';
    }
}