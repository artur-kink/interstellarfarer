#ifndef _STATICSPRITE_
#define _STATICSPRITE_

#include "BaseSprite.hpp"

/**
* The most basic sprite that represents a static unchanging part of a texture.
*/
class StaticSprite: public BaseSprite {
protected:
    SDL_Texture* texture;

public:

    StaticSprite(int spriteSheet, int spriteIndex, int x, int y, int w, int h);
    StaticSprite(int spriteSheet, int spriteIndex, SDL_Texture* t, int x, int y, int w, int h);

    virtual BaseSprite* copy();
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* dest) const;
    virtual SDL_Texture* getTexture();
    virtual ~StaticSprite();
};

#endif
