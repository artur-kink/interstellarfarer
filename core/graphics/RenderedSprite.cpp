#include "RenderedSprite.hpp"

RenderedSprite::RenderedSprite(){
    type = BaseSprite::st_Static;
    init(32, 32);
}

RenderedSprite::RenderedSprite(int w, int h){
    type = BaseSprite::st_Static;
    init(w, h);
}

void RenderedSprite::init(int w, int h){
	width = (float)w;
	height = (float)w;

}

BaseSprite* RenderedSprite::copy(){
    return 0;
}

void RenderedSprite::clear(){

}

void RenderedSprite::render(BaseSprite* sprite){

}

void RenderedSprite::draw(SDL_Renderer* renderer, SDL_Rect* dest) const{

}

RenderedSprite::~RenderedSprite(){

}
