#include "LayeredSprite.hpp"

/**
* Create layered sprite with expected layer count and sprite index.
* @param count Number of layers to allocate.
* @param spriteIndex Index of the sprite.
*/
LayeredSprite::LayeredSprite(byte count,  unsigned short spriteIndex){
    type = BaseSprite::st_Layered;
    layerCount = count;
    index = spriteIndex;
    layers = new BaseSprite*[count];
    memset(layers, 0, sizeof(BaseSprite*)*count);
    name = 0;
}

/**
* Updates the layered sprite. This is necessary since the layered sprite
* might contain dynamic sprites within it. Nothing in the current sprite
* is modified. Update calls are made to all dynamic layers.
*/
void LayeredSprite::update(int currentTime){
    for(int i = 0; i < layerCount; i++){
        //Check if layer is dynamic.
        DynamicSprite* sprite = dynamic_cast<DynamicSprite*>(layers[i]);
        if(sprite != 0){
            sprite->update(currentTime);
        }
    }
}

/**
* Copies instance of layered sprite.
*/
BaseSprite* LayeredSprite::copy(){
    LayeredSprite* sprite = new LayeredSprite(layerCount, index);
    width = sprite->width;
    height = sprite->height;

    sprite->name = name;
    //Copy layers.
    for(int i = 0; i < layerCount; i++){
        sprite->layers[i] = layers[i]->copy();
    }
    return sprite;
}

void LayeredSprite::draw(SDL_Renderer* renderer, SDL_Rect* dest) const{
    for(int i = 0; i < layerCount; i++){
        layers[i]->draw(renderer, dest);
    }
}

/**
* Deletes layers from memory. No sprites are deleted.
* @todo Currently memory leaks if this is a copy.
*/
LayeredSprite::~LayeredSprite(){
    if(layerCount != 0){
        for(int i = 0; i < layerCount; i++){
            layers[i] = 0;
        }
        delete layers;
        layers = 0;
    }
}
