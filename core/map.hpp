#ifndef _MAP_
#define _MAP_

#include "core.hpp"

class Map{
protected:

public:

    byte width;
    byte height;

    byte* tiles;

    Map();

    void init(byte w, byte h);
};

#endif
