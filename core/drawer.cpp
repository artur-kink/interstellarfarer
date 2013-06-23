#include "drawer.hpp"

void Drawer::draw(SDL_Renderer* renderer, Ship* ship){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.w = 32; rect.h = 32;
    for(byte r = 0; r < ship->map.height; r++){
        rect.y = r*32;
        for(byte c = 0; c < ship->map.width; c++){

            if(ship->map.tiles[r*ship->map.width + c] == 1){
                rect.x = c*32;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    rect.x = (InputHandler::I()->mouseX/32)*32;
    rect.y = (InputHandler::I()->mouseY/32)*32;
    SDL_RenderDrawRect(renderer, &rect);
}