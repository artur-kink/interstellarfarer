#ifndef _RENDEREDSPRITE_
#define	_RENDEREDSPRITE_

#include "BaseSprite.hpp"

class RenderedSprite: public BaseSprite{
protected:

public:


    RenderedSprite();
    RenderedSprite(int w, int h);

    virtual BaseSprite* copy();
    void init(int w, int h);
	void clear();
    void render(BaseSprite* sprite);
    virtual void draw(SDL_Renderer* renderer, SDL_Rect* dest) const;
    virtual ~RenderedSprite();
};

#endif

