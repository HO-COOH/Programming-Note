#ifndef INCLUDE_TRAY_H
#define INCLUDE_TRAY_H

#include "Item.h"
#include <vector>
#include <memory>

namespace factory
{
    class Tray : public Item
    {
    protected:
        std::vector<std::unique_ptr<Item>> tray;
    public:
        Tray(std::string caption);
        void add(std::unique_ptr<Item>&& item);
    };
}

#endif /* INCLUDE_TRAY_H */
