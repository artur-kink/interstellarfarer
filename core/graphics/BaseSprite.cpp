#include "BaseSprite.hpp"

BaseSprite::BaseSprite(){
    name = 0;
}

/** 
* Does not delete sprite name.
* Sprite name is deleted by SpriteNameIndex in SpriteManager.
*/
BaseSprite::~BaseSprite(){
    name = 0;
}
