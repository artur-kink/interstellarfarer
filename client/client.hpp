#ifndef _CLIENT_
#define _CLIENT_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../core/ship.hpp"
#include "../core/inputhandler.hpp"
#include "../core/drawer.hpp"

#include "../core/shiplist.hpp"
#include "../core/modulelist.hpp"
#include "../core/shipmodule.hpp"

#include "../core/graphics/SpriteManager.hpp"

///
/// Core game client code.
///
class Client{
protected:
    SDL_Window* window;
    SDL_Renderer *renderer;

    bool runClient;
    Uint32 frameTime;

    InputHandler inputHandler;

    Ship ship;

    ShipList ships;
    ModuleList modules;

    SpriteManager spriteManager;
public:
    Client();

    int initSDL();
    void cleanupSDL();

    void run();
    void update();

    void draw();
};

#endif
