#ifndef _MAP_
#define _MAP_

#include "core.hpp"

enum TileType{
    tt_Free = 0,
    tt_Empty = 1,
    tt_Blocked = 255
};

class Map{
protected:

public:

    byte width;
    byte height;

    byte* tiles;

    Map();

    void init(byte w, byte h);

    ~Map();
};

#endif
