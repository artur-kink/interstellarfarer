#include "map.hpp"

Map::Map(){
    tiles = 0;
}

/**
 * Initialize empty map of size w*h.
 * @param w Map width
 * @param h Map height
 */
void Map::init(byte w, byte h){
    width = w;
    height = h;

    tiles = new byte[width*height];
    for(unsigned short i = 0; i < width*height; i++){
        tiles[i] = tt_Blocked;
    }
}

/**
 * Cleanup map memory.
 */
Map::~Map(){
    //Delete tiles if initialized
    if(tiles){
        delete tiles;
        tiles = 0;
    }
}
