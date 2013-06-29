#ifndef _BASESPRITE_
#define _BASESPRITE_

#include <SDL.h>
#include <cstring>

#include "../core.hpp"

#ifndef NO_SPRITE
#define NO_SPRITE 65535
#endif

/**
* A base class for all Sprites.
* These classes are used to encapsulate all drawable sprites.
*/
class BaseSprite{
public:

    /**
    * The sprite's type.
    */
    enum SpriteType{
        /**
        * A static unchangeable sprite.
        */
        st_Static,
        /**
        * A compilation of multiple sprites.
        */
        st_Layered,
        /**
        * An animated sprite that is a collection of static sprites.
        */
        st_Animated
	};

    /**
    * Sprite index in the full sprite list.
    */
    unsigned short index;

    /**
    * Spritesheet index.
    */
    int sheet;

    /**
    * The sprite's type.
    */
    SpriteType type;


    /**
    * Pointer to the name of the sprite.
    * Note that this pointer is shared with the spriteNames list
    * of SpriteManager. The names are managed by the sprite manager
    * and therefore this pointer should not be allocated or released.
    */
    char* name;

    /**
    * The size of this sprite. This is specifically useful in the dynamic sprites.
    */
    int width, height;

    int x, y;

    BaseSprite();

    /**
    * Copy constructor for sprites.
    * @return Copy of the current instance.
    */
    virtual BaseSprite* copy() = 0;

    /**
    * Draws to the specified target.
    */
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* dest) const = 0;

    virtual ~BaseSprite();
};

#endif
