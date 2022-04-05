#ifndef INCLUDE_PAGE_H
#define INCLUDE_PAGE_H
#include "Item.h"
#include <vector>
#include <memory>

namespace factory
{
    class Page
    {
    protected:
        std::string title;
        std::string author;
        std::vector<std::unique_ptr<Item>> items;
    public:
        Page(std::string title, std::string author);
        void add(std::unique_ptr<Item>&& item);
        void output() const;
        std::string makeHTML() const;
    };
}

#endif /* INCLUDE_PAGE_H */
