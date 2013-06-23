#ifndef _DRAWER_
#define _DRAWER_

#include <SDL.h>
#include <SDL_image.h>

#include "ship.hpp"
#include "inputhandler.hpp"

class Drawer{
public:
    static void draw(SDL_Renderer* renderer, Ship* ship);

};

#endif
