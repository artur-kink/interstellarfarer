#ifndef _SHIP_
#define _SHIP_

#include <vector>

#include "graphics/BaseSprite.hpp"
#include "map.hpp"
#include "module.hpp"
#include "shipmodule.hpp"


class Ship{
protected:

public:
    BaseSprite* sprite;

    std::string name;
    std::vector<ShipModule*> modules;
    Map map;

    Ship();
    void init(Ship* ship);
    void placeModule(ShipModule* module, int x, int y);
};

#endif
