#ifndef _ANIMATEDSPRITE_
#define _ANIMATEDSPRITE_

#include "BaseSprite.hpp"
#include "DynamicSprite.hpp"

/**
* A frame in an animated sprite.
*/
struct SpriteFrame {
    unsigned short index;
    BaseSprite* sprite;
    unsigned short duration;
};

/**
* An animated sprite composed of timed frames consisting of other sprites.
*/
class AnimatedSprite : public DynamicSprite {
public:
    /**
    * Frames in this sprite.
    */
    SpriteFrame* frames;

    /**
    * Number of frames.
    */
    byte frameCount;

    /**
    * The frame index being currently shown.
    */
    byte currentFrame;

    AnimatedSprite(byte count, unsigned short spriteIndex);
    int getFrameIndex();
    virtual void update(int currentTime);

    virtual BaseSprite* copy();
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* dest) const;
    virtual ~AnimatedSprite();
};

#endif
