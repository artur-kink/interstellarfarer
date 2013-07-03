#ifndef _SHIPMODULE_
#define _SHIPMODULE_

#include "module.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/BaseSprite.hpp"

/**
 * A module that is placed on a ship.
 * @see Module
 * @see Ship
 */
class ShipModule{
private:

public:
    /** This ShipModule base module type */
    Module* module;

    /** Current health of module */
    int health;

    /** Current power consumtion of module */
    int power;

    /** Y tile of module on ship */
    int y;
    /** X tile of module on ship */
    int x;

    ShipModule();
    ShipModule(Module* m);

    void init(Module* m);

    void draw(SDL_Renderer* renderer);
};

#endif
