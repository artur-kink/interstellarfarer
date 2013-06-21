#ifndef _CLIENT_
#define _CLIENT_

#include <iostream>
#include <SDL.h>

///
/// Core game client code.
///
class Client{
protected:
    SDL_Window* window;
    bool runClient;

public:
    Client();

    int initSDL();
    void cleanupSDL();

    void run();
};

#endif
