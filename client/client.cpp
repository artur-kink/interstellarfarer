#include "client.hpp"

Client::Client(){
    window = 0;
}

int Client::initSDL(){
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    initResult = IMG_Init(IMG_INIT_PNG);
    if(initResult&IMG_INIT_PNG != IMG_INIT_PNG){
        std::cout << "Failed to init IMG: " << IMG_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Test", 0, 0, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Check if window was created
    if(!window){
        return 1;
    }

    spriteManager.renderer = renderer;
    spriteManager.loadRawSprites("sprites");

    ships.load(&spriteManager);
    modules.load(&spriteManager);

    ship.init(ships.ships.at(0));

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

    if(inputHandler.leftDown){
        int tileX = (inputHandler.mouseX/32);
        int tileY = (inputHandler.mouseY/32);

        if(tileX < ship.map.width && tileY < ship.map.height){
            if(inputHandler.isKeyPressed(SDL_SCANCODE_R)){
                if(ship.map.tiles[tileY*ship.map.width + tileX] == 1){
                    cout << "Adding module" << endl;
                    ship.placeModule(new ShipModule(modules.modules.at(0)), tileX, tileY);
                }
            }else{
                if(ship.map.tiles[tileY*ship.map.width + tileX] != tt_Blocked)
                    ship.map.tiles[tileY*ship.map.width + tileX] = 1;
            }
        }
    }
    if(inputHandler.rightDown){
        int tileX = (inputHandler.mouseX/32);
        int tileY = (inputHandler.mouseY/32);

        if(tileX < ship.map.width && tileY < ship.map.height)
            if(ship.map.tiles[tileY*ship.map.width + tileX] != tt_Blocked)
                ship.map.tiles[tileY*ship.map.width + tileX] = 0;
    }
}

void Client::draw(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Drawer::draw(renderer, &ship);

    SDL_RenderPresent(renderer);
}
