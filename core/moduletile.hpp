#ifndef _MODULETILE_
#define _MODULETILE_

#include "graphics/BaseSprite.hpp"

enum ModuleTileType{
    mtt_Manned,
    mtt_Free = 0,
    mtt_Blocked
};

class ModuleTile{
public:
    ModuleTile();

    int x;
    int y;

    BaseSprite* sprite;

    ModuleTileType type;
};

#endif
