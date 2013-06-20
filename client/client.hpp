#ifndef _CLIENT_
#define _CLIENT_

#include <SDL.h>

class Client{
protected:
    SDL_Window* window;

public:
    Client();

    int initSDL();
    void cleanupSDL();

    void run();
};

#endif
