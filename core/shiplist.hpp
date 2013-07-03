#ifndef _SHIPLIST_
#define _SHIPLIST_

#include <vector>
#include "ship.hpp"
#include "graphics/SpriteManager.hpp"

/**
 * List of Ship definitions
 * @see Ship
 */
class ShipList{
private:

public:
    /** Ship definitions */
    std::vector<Ship*> ships;

    ShipList();

    void load(SpriteManager* sprites);

};

#endif
