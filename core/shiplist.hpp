#ifndef _SHIPLIST_
#define _SHIPLIST_

#include <vector>
#include "ship.hpp"
#include "graphics/SpriteManager.hpp"

class ShipList{
private:

public:
    std::vector<Ship*> ships;

    ShipList();

    void load(SpriteManager* sprites);

};

#endif
