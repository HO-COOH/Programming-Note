#include "listfactory/ListLink.h"

namespace listfactory
{
    ListLink::ListLink(std::string caption, std::string url)
        : Link(std::move(caption), std::move(url))
    {
    }

    std::string ListLink::makeHTML() const
    {
        return "<li><a href=\"" + url + "\">" + caption + "</a></li>\n";
    }
}