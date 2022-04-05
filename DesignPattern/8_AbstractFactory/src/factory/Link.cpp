#include "factory/Link.h"

namespace factory
{
    Link::Link(std::string caption, std::string url)
        : Item(std::move(caption))
        , url(std::move(url))
    {
    }
}