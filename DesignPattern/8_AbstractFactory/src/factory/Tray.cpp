#include "factory/Tray.h"

namespace factory
{
    Tray::Tray(std::string caption)
        : Item(std::move(caption))
    {
    }

    void Tray::add(std::unique_ptr<Item>&& item)
    {
        tray.push_back(std::move(item));
    }
}