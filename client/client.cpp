#include "client.hpp"

Client::Client(){
    window = 0;
    map.init(11, 11);
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
    SDL_DestroyRenderer(renderer);
    renderer = 0;
    SDL_DestroyWindow(window);
    window = 0;
    IMG_Quit();
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
        SDL_PumpEvents();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_WINDOWEVENT){
                if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                    runClient = false;
                    std::cout << "Window closing" << std::endl;
                }
            }
        }
        inputHandler.update(frameTime);
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.w = 32; rect.h = 32;
    for(byte r = 0; r < map.height; r++){
        rect.y = r*32;
        for(byte c = 0; c < map.width; c++){

            if(map.tiles[r*map.width + c] == 1){
                rect.x = c*32;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    rect.x = (inputHandler.mouseX/32)*32;
    rect.y = (inputHandler.mouseY/32)*32;
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}
