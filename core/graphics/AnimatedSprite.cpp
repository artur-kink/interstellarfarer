#include "AnimatedSprite.hpp"

/**
* Create empty animated sprite with count expected frames and sprite index.
* @param count Number of frames to allocate.
* @param spriteIndex Index of the sprite.
*/
AnimatedSprite::AnimatedSprite(byte count, unsigned short spriteIndex){
    type = BaseSprite::st_Animated;

    index = spriteIndex;
    frameCount = count;
    currentFrame = 0;
    frames = new SpriteFrame[count];
    lastUpdate = 0;
    name = 0;
}

/**
* Copy instance of animated sprite.
*/
BaseSprite* AnimatedSprite::copy(){
    AnimatedSprite* sprite = new AnimatedSprite(frameCount, index);
    width = sprite->width;
    height = sprite->height;
    sprite->name = name;

    //Copy frames
    for(int i = 0; i < frameCount; i++){
        sprite->frames[i].duration = frames[i].duration;
        sprite->frames[i].index = frames[i].index;
        sprite->frames[i].sprite = frames[i].sprite->copy();
    }
    return sprite;
}

/**
* Gets sprite index of the current frame.
*/
int AnimatedSprite::getFrameIndex(){
    return frames[currentFrame].index;
}

/**
* Updates the animated sprite. If duration of the frame has exceeded then the
* sprite switches to the next frame.
* @param currentTime The current time.
*/
void AnimatedSprite::update(int currentTime){
    if(currentTime - lastUpdate > frames[currentFrame].duration){
        lastUpdate = currentTime;
        currentFrame++;
        if(currentFrame >= frameCount)
            currentFrame = 0;
        width = frames[currentFrame].sprite->width;
        height = frames[currentFrame].sprite->height;
    }
}

void AnimatedSprite::draw(SDL_Renderer* renderer, SDL_Rect* dest) const{
    frames[currentFrame].sprite->draw(renderer, dest);
}

/**
* Deletes frames from memory.
*/
AnimatedSprite::~AnimatedSprite(){
    for(int i = 0; i < frameCount; i++){
        frames[i].sprite = 0;
    }
    delete frames;
    frames = 0;
}
