#include "shipmodule.hpp"

ShipModule::ShipModule(){
    x = y = 0;
}

ShipModule::ShipModule(Module* m){
    init(m);
}

void ShipModule::init(Module* m){
    module = m;

    power = module->power;
    health = module->health;
}

void ShipModule::draw(SDL_Renderer* renderer){

    SDL_Rect rect;
    for(byte t = 0; t < module->tiles.size(); t++){
        ModuleTile* tile = &(module->tiles.at(t));
        if(tile->sprite){
            rect.x = (x + tile->x)*32;
            rect.y = (y + tile->y)*32;
            rect.w = module->overlaySprite->width;
            rect.h = module->overlaySprite->height;
            tile->sprite->draw(renderer, &rect);
        }
    }
}
