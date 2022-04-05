#include "factory/Item.h"

namespace factory
{
    Item::Item(std::string&& caption)
        : caption(std::move(caption))
    {
    }
}