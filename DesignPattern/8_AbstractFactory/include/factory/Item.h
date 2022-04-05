#ifndef INCLUDE_ITEM_H
#define INCLUDE_ITEM_H

#include <string>
namespace factory
{
    class Item
    {
    protected:
        std::string caption;
    public:
        Item(std::string&& caption);
        virtual std::string makeHTML() = 0;
    };
}

#endif /* INCLUDE_ITEM_H */
