#include "client.hpp"

Client::Client(){
    window = 0;
}

int Client::initSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Test", 0, 0, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Check if window was created
    if(!window){
        return 1;
    }
    return 0;
}

void Client::cleanupSDL(){
    //Cleanup
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Client::run(){
    frameTime = SDL_GetTicks();
    Uint32 updateAccumulator = 0;

    //Main game loop
    runClient = true;
    while(runClient){
        Uint32 currenTime = SDL_GetTicks();
        updateAccumulator += currenTime - frameTime;
        frameTime = currenTime;

        //Check for window events
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_WINDOWEVENT){
                if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                    runClient = false;
                    std::cout << "Window closing" << std::endl;
                }
            }
        }

        while(updateAccumulator >= 20){
            updateAccumulator -= 20;
            update();
        }

        draw();
        SDL_Delay(1);
    }

}

void Client::update(){

}

void Client::draw(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
