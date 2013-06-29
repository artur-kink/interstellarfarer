#ifndef _MODULE_
#define _MODULE_

#include <string>
#include <vector>

#include "moduletile.hpp"

class Module{
public:
    std::string name;
    std::string storeIcon;
    std::string hudIcon;
    std::string overlayIcon;

    int price;
    int health;
    int power;

    std::vector<ModuleTile> tiles;

    bool extension;
    bool extendable;
    int extensionLimit;
    std::vector<Module*> extensions;

    Module();
};

#endif
