#ifndef _SHIPMODULE_
#define _SHIPMODULE_

#include "module.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/BaseSprite.hpp"

class ShipModule{
private:

public:
    Module* module;
    int health;
    int power;

    int y;
    int x;

    ShipModule();
    ShipModule(Module* m);

    void init(Module* m);

    void draw(SDL_Renderer* renderer);
};

#endif
