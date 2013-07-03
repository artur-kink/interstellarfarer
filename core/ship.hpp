#ifndef _SHIP_
#define _SHIP_

#include <vector>

#include "graphics/BaseSprite.hpp"
#include "map.hpp"
#include "module.hpp"
#include "shipmodule.hpp"

/**
 * Ship definition and all the assossiated gameplay mechanics of a Ship.
 * @see Module
 * @see ShipModule
 * @see Map
 */
class Ship{
protected:

public:
    /** Ship's image sprite */
    BaseSprite* sprite;

    /** Ship name */
    std::string name;

    /** List of modules on this Ship */
    std::vector<ShipModule*> modules;

    /** Map of the ship */
    Map map;

    Ship();
    void init(Ship* ship);
    void placeModule(ShipModule* module, int x, int y);
};

#endif
