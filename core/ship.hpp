#ifndef _SHIP_
#define _SHIP_

#include <vector>

#include "map.hpp"
#include "module.hpp"

class Ship{
protected:
    std::vector<Module*> modules;

public:
    Map map;

    Ship();
};

#endif
