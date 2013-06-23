#include "map.hpp"

Map::Map(){
    tiles = 0;
}

void Map::init(byte w, byte h){
    width = w;
    height = h;

    tiles = new byte[width*height];
    for(unsigned short i = 0; i < width*height; i++){
        tiles[i] = 0;
    }
}


Map::~Map(){
    if(tiles){
        delete tiles;
        tiles = 0;
    }
}
