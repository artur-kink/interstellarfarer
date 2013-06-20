#include "client.hpp"

Client::Client(){
    window = 0;

}

int Client::initSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Test", 0, 0, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

    //Check if window was created
    if(!window){
        return 1;
    }
    return 0;
}

void Client::cleanupSDL(){
    //Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Client::run(){
    while(1){
        SDL_Delay(5);
    }
}
