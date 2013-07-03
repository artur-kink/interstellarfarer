#ifndef _MODULE_
#define _MODULE_

#include <string>
#include <vector>

#include "moduletile.hpp"
#include "graphics/BaseSprite.hpp"

/**
 * A Module is an object that can be placed
 * on a Ship, such as weapons etc...
 * @see Ship
 */
class Module{
public:
    /** Module name */
    std::string name;

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
