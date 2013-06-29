#ifndef _LAYEREDSPRITE_
#define _LAYEREDSPRITE_
#include "BaseSprite.hpp"
#include "DynamicSprite.hpp"
#include <cstring>

/**
* A sprite composed of multiple sprites drawn ontop of each other.
*/
class LayeredSprite : public BaseSprite {
private:

public:
    /**
    * Sprite layers.
    */
    BaseSprite** layers;

    /**
    * Number of layers.
    */
    byte layerCount;

    LayeredSprite(byte count, unsigned short spriteIndex);
    virtual void update(int currentTime);
    virtual BaseSprite* copy();
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* dest) const;
    virtual ~LayeredSprite();
};

#endif

