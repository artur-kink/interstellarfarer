#ifndef _SPRITEMANAGER_
#define _SPRITEMANAGER_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <pugixml.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "StaticSprite.hpp"
#include "AnimatedSprite.hpp"
#include "LayeredSprite.hpp"
#include "SpriteSet.hpp"

using namespace std;

/**
* This class is used to load, access and manage sprites specified in sprite .dat files.
*/
class SpriteManager {
private:

    /**
    * A name/index key value pair to match names to indeces.
    */
    struct SpriteNameIndex{
        char* name;
        unsigned short index;
    };

    /**
    * This list contains all sprites that can be updated.
    */
    vector<DynamicSprite*> dynamicList;

public:

    SDL_Renderer* renderer;

    /**
    * The loaded sprites.
    */
    BaseSprite** sprites;

    /**
    * Index of sprite names;
    */
    SpriteNameIndex* spriteNames;

    /**
    * Number of sprites.
    */
    unsigned short spriteCount;

    /**
    * Sprite sets.
    */
    SpriteSet** spriteSets;

    /**
    * Index of sprite set names;
    */
    SpriteNameIndex* spriteSetNames;

    /**
    * Number of sprites.
    */
    unsigned short spriteSetCount;

    /**
    * Textures used by sprites.
    */
    SDL_Texture** textures;
    char** textureNames;

    /**
    * Number of sprite sheets.
    */
    unsigned char sheetCount;

    SpriteManager();

    void loadSprites(const char* file);

    void addDynamicSprite(DynamicSprite* sprite);
    void removeDynamicSprite(DynamicSprite* sprite);

    void loadRawSprites(const char* file);
    void saveSprites(const char* file);
    int getStringIndex(vector<char*>* strings, const char* name);

    BaseSprite* getSprite(unsigned short index);
    BaseSprite* getSpriteCopy(unsigned short index);
    unsigned short getSpriteIndex(const char* name);
    BaseSprite* getSprite(const char* name);
    void deleteSprite(BaseSprite* sprite);

    SpriteSet* getSpriteSet(const char* name);

    unsigned short findName(SpriteNameIndex* list, unsigned short listSize, const char* name);

    void update(unsigned int time);

    ~SpriteManager();
};

#endif
