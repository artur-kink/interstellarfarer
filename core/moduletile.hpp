#ifndef _MODULETILE_
#define _MODULETILE_

enum ModuleTileType{
    Manned, Free, Blocked
};

class ModuleTile{
public:
    ModuleTile();

    int x;
    int y;
    ModuleTileType type;
};

#endif
