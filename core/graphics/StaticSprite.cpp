#include "StaticSprite.hpp"

/**
* Create static sprite with provided texture.
*/
StaticSprite::StaticSprite(int spriteSheet, int spriteIndex, SDL_Texture* t, int x, int y, int w, int h){
    type = BaseSprite::st_Static;
    sheet = spriteSheet;
    index = spriteIndex;
    texture = t;
    this->x = x;
    this->y = y;
    width = (float)w;
    height = (float)h;
    name = 0;
}

/**
* Create static sprite without specified texture.
*/
StaticSprite::StaticSprite(int spriteSheet, int spriteIndex, int x, int y, int w, int h){
    sheet = spriteSheet;
    index = spriteIndex;
    this->x = x;
    this->y = y;
    width = (float)w;
    height = (float)h;
    name = 0;
}

/**
* Copy instance of static sprite.
*/
BaseSprite* StaticSprite::copy(){
    StaticSprite* sprite = new StaticSprite(sheet, index, texture,
            x, y, width, height);
    sprite->name = name;
    return sprite;
}

/**
* Get SDL Texture
*/
SDL_Texture* StaticSprite::getTexture(){
    return texture;
}

/**
* Draw this sprite to the target.
*/
void StaticSprite::draw(SDL_Renderer* renderer, SDL_Rect* dest) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(renderer, texture, &rect, dest);
}

/**
* Doesn't delete anything. Name and texture references should be deleted
* by SpriteManager.
*/
StaticSprite::~StaticSprite(){
}
