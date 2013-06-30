#ifndef _MODULE_
#define _MODULE_

#include <string>
#include <vector>

#include "moduletile.hpp"
#include "graphics/BaseSprite.hpp"

class Module{
public:
    std::string name;
    std::string storeIcon;
    std::string hudIcon;
    std::string overlayIcon;

    BaseSprite* storeSprite;
    BaseSprite* hudSprite;
    BaseSprite* overlaySprite;

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
