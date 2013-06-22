#ifndef _CLIENT_
#define _CLIENT_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

///
/// Core game client code.
///
class Client{
protected:
    SDL_Window* window;
    SDL_Renderer *renderer;

    bool runClient;
    Uint32 frameTime;

public:
    Client();

    int initSDL();
    void cleanupSDL();

    void run();
    void update();

    void draw();
};

#endif
