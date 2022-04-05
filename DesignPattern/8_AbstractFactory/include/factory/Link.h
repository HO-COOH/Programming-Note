#ifndef INCLUDE_LINK_H
#define INCLUDE_LINK_H

#include "Item.h"
namespace factory
{
    class Link : public Item
    {
    protected:
        std::string url;
    public:
        Link(std::string caption, std::string url);
    };
}

#endif /* INCLUDE_LINK_H */
