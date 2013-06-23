#ifndef _CLIENT_
#define _CLIENT_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../core/map.hpp"
#include "../core/inputhandler.hpp"

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

    Map map;

public:
    Client();

    int initSDL();
    void cleanupSDL();

    void run();
    void update();

    void draw();
};

#endif
