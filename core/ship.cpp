#include "ship.hpp"

Ship::Ship(){
}

/**
 * Initialize this instance of a Ship based on the given Ship.
 * @param ship Base ship information to copy as source.
 */
void Ship::init(Ship* ship){
    name = ship->name;
    sprite = ship->sprite;

    //Copy ship layout.
    map.init(ship->map.width, ship->map.height);
    for(byte h = 0; h < map.height; h++){
        for(byte w = 0; w < map.width; w++){
            map.tiles[h*map.width + w] = ship->map.tiles[h*map.width + w];
        }
    }
}

/**
 * Place a Module on this Ship at given location. Adds
 * the module to the ship.
 * @param module Module to place.
 * @param x X location in tiles.
 * @param y Y location in tiles.
 */
void Ship::placeModule(ShipModule* module, int x, int y){
    module->x = x;
    module->y = y;

    for(int i = 0; i < module->module->tiles.size(); i++){
        ModuleTile& tile = module->module->tiles.at(i);
        map.tiles[(y + tile.y)*map.width + (x + tile.x)] = 2;
    }

    modules.push_back(module);
}
