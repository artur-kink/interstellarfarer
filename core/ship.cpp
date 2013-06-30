#include "ship.hpp"

Ship::Ship(){
}

void Ship::init(Ship* ship){
    name = ship->name;
    sprite = ship->sprite;
    map.init(ship->map.width, ship->map.height);
    for(byte h = 0; h < map.height; h++){
        for(byte w = 0; w < map.width; w++){
            map.tiles[h*map.width + w] = ship->map.tiles[h*map.width + w];
        }
    }
}

void Ship::placeModule(ShipModule* module, int x, int y){
    module->x = x;
    module->y = y;
    modules.push_back(module);
}
