#ifndef _MAP_
#define _MAP_

#include "core.hpp"

/**
 * Tile type code.
 */
enum TileType{
    /** Tile can be drawn in */
    tt_Free = 0,
    /** Tile has been drawn */
    tt_Empty = 1,
    /** Tile cannot be drawn */
    tt_Blocked = 255
};

/**
 * Tile based map for ships, stations etc...
 */
class Map{
protected:

public:

    byte width; /** Map width in tiles */
    byte height; /**Map height in tiles */

    /** Tile array */
    byte* tiles;

    Map();

    void init(byte w, byte h);

    ~Map();
};

#endif
