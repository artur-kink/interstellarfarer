#include "SpriteManager.hpp"

SpriteManager::SpriteManager(){

}

/**
* Gets sprite by sprite index.
*/
BaseSprite* SpriteManager::getSprite(unsigned short index){
    if(index != NO_SPRITE){
        return sprites[index];
    }
    return 0;
}

/**
* Gets a copy of the sprite at index.
* If the sprite is updateable then it is added to the update list.
* @return Copy of the sprite at index.
*/
BaseSprite* SpriteManager::getSpriteCopy(unsigned short index){
    BaseSprite* sprite = getSprite(index);
    if(sprite != 0){
        BaseSprite* copy = sprite->copy();
        if(copy->type == BaseSprite::st_Animated || copy->type == BaseSprite::st_Layered)
            addDynamicSprite((DynamicSprite*) copy);
        return copy;
    }
    return 0;
}

/**
* Deletes the specified sprite from memory.
* This is used to clear clear copied sprites.
* @param sprite Sprite to delete.
*/
void SpriteManager::deleteSprite(BaseSprite* sprite){
    if(sprite != 0){
        if(dynamic_cast<DynamicSprite*> (sprite) != 0)
            removeDynamicSprite((DynamicSprite*) sprite);

        delete sprite;
        sprite = 0;
    }
}

/**
* Updates all dynamic sprites.
*/
void SpriteManager::update(unsigned int time){
    for(unsigned int i = 0; i < dynamicList.size(); i++){
        dynamicList.at(i)->update(time);
    }
}

/**
* Add a dynamic sprite to the dynamic sprite list.
*/
void SpriteManager::addDynamicSprite(DynamicSprite* sprite){
    dynamicList.push_back(sprite);
}

/**
* Remove dynamic sprite from the dynamic sprite list.
*/
void SpriteManager::removeDynamicSprite(DynamicSprite* sprite){
    for(unsigned int i = 0; i < dynamicList.size(); i++){
        if(dynamicList.at(i) == sprite){
            dynamicList.erase(dynamicList.begin() + i);
            break;
        }
    }
}

/**
* Loads sprite definitions from a .dat file.
* @param file dat file to load from.
*/
void SpriteManager::loadSprites(const char* file){

    //Open file
    ifstream fileStream;
    fileStream.open(file, ios::in | ios::binary);
    fileStream.seekg(0);

    //If file exists
    if(fileStream.good()){
        //Get sprite sheets
        unsigned char numSheets = 0;
        fileStream.read((char*) &numSheets, sizeof numSheets);
        cout << "Sprites Sheets Found: " << numSheets << endl;

        //Load textures associated with sprite sheets
        textures = new SDL_Texture*[numSheets];
        textureNames = new char*[numSheets];
        for(unsigned char i = 0; i < numSheets; i++){
            unsigned char sheetNameLength = 0;
            fileStream.read((char*) &sheetNameLength, sizeof(sheetNameLength));
            char* sheetNameChr = new char[sheetNameLength + 1];
            fileStream.read(sheetNameChr, sheetNameLength);
            sheetNameChr[sheetNameLength] = '\0';

			//Load texture file
            SDL_Surface* textureSurface = IMG_Load(sheetNameChr);
            if(!textureSurface){
                cout << "Failed to load sprite sheet: " << sheetNameChr << endl;
                continue;
            }

            textureNames[i] = sheetNameChr;
            cout << "Loaded Sheet: " << sheetNameChr << endl;
        }
        sheetCount = numSheets;

        //Load sprite definitions
        unsigned short numSprites = 0;
        fileStream.read((char*) &numSprites, sizeof numSprites);
        sprites = new BaseSprite*[numSprites];
        spriteCount = numSprites;

        cout << "Sprites Found: " << numSprites << endl;
        for(unsigned int i = 0; i < numSprites; i++){
            unsigned char spriteType = 0;
            fileStream.read((char*) &spriteType, sizeof spriteType);
            if(spriteType == 0){ //Static Sprite
                int sheet = 0;
                int x = 0;
                int y = 0;
                int width = 0;
                int height = 0;
                fileStream.read((char*) &sheet, sizeof sheet);
                fileStream.read((char*) &x, sizeof x);
                fileStream.read((char*) &y, sizeof y);
                fileStream.read((char*) &width, sizeof width);
                fileStream.read((char*) &height, sizeof height);
                StaticSprite* sprite = new StaticSprite(sheet, i, textures[sheet], x, y, width, height);
                sprites[i] = sprite;
                cout << "Loaded Sprite: " << sheet << ", " << x << "x" << y << ", " << width << "x" << height << endl;
            }else if(spriteType == 1){ //Animated Sprite
                unsigned char frameCount = 0;
                fileStream.read((char*) &frameCount, sizeof frameCount);
                AnimatedSprite* sprite = new AnimatedSprite(frameCount, i);
                //Load animated sprite frames
                for(int j = 0; j < frameCount; j++){
                    unsigned short index = 0;
                    unsigned short duration = 0;
                    fileStream.read((char*) &index, sizeof index);
                    fileStream.read((char*) &duration, sizeof duration);
                    sprite->frames[j].index = index;
                    sprite->frames[j].duration = duration;
                    sprite->frames[j].sprite = getSprite(index);
                }
                sprite->width = sprite->frames[0].sprite->width;
                sprite->height = sprite->frames[0].sprite->height;
                addDynamicSprite(sprite);
                sprites[i] = sprite;
            }else if(spriteType == 2){ //Layered Sprite
                unsigned char layerCount = 0;
                fileStream.read((char*) &layerCount, sizeof layerCount);
                LayeredSprite* sprite = new LayeredSprite(layerCount, i);
                //Load layered sprite layers
                for(int j = 0; j < spriteType; j++){
                    unsigned short index = 0;
                    fileStream.read((char*) &index, sizeof index);
                    sprite->layers[j] = getSprite(index);
                }
                sprite->width = sprite->layers[0]->width;
                sprite->height = sprite->layers[0]->height;
                sprites[i] = sprite;
            }
        }

        //Load ordered sprite name index
        spriteNames = new SpriteNameIndex[numSprites];
        for(unsigned int i = 0; i < numSprites; i++){
            unsigned short index = 0;
            fileStream.read((char*) &index, sizeof index);
            spriteNames[i].index = index;
            byte nameLen = 0;
            fileStream.read((char*) &nameLen, sizeof nameLen);
            spriteNames[i].name = new char[nameLen + 1];
            fileStream.read(spriteNames[i].name, nameLen);
            spriteNames[i].name[nameLen] = '\0';
            sprites[index]->name = spriteNames[i].name;
        }

        //Load sprite sets
        fileStream.read((char*) &spriteSetCount, sizeof spriteSetCount);
        spriteSets = new SpriteSet*[spriteSetCount];
        for(unsigned int i = 0; i < spriteSetCount; i++){
            byte spriteSetSize = 0;
            fileStream.read((char*) &spriteSetSize, sizeof(spriteSetSize));
            spriteSets[i] = new SpriteSet(spriteSetSize);
            for(int j = 0; j < spriteSetSize; j++){
                unsigned short spriteIndex = 0;
                fileStream.read((char*) &spriteIndex, sizeof(spriteIndex));
                spriteSets[i]->sprites[j] = getSprite(spriteIndex);
            }
        }

        //Load ordered sprite set name index
        spriteSetNames = new SpriteNameIndex[spriteSetCount];
        for(unsigned int i = 0; i < spriteSetCount; i++){
            unsigned short index = 0;
            fileStream.read((char*) &index, sizeof index);
            spriteSetNames[i].index = index;
            byte nameLen = 0;
            fileStream.read((char*) &nameLen, sizeof nameLen);
            spriteSetNames[i].name = new char[nameLen + 1];
            fileStream.read(spriteSetNames[i].name, sizeof(char) * nameLen);
            spriteSetNames[i].name[nameLen] = '\0';
        }

        cout << "Sprites loaded" << endl;
    }
}

/**
* Loads the raw xml sprite definition file.
*/
void SpriteManager::loadRawSprites(const char* file){
    //Open xml document.
    pugi::xml_document doc;
    char* sourceFile = new char[strlen(file) + 5];
    strcpy(sourceFile, file);
    strcat(sourceFile, ".xml");
    pugi::xml_parse_result loadResult = doc.load_file(sourceFile);

    cout << "Load Result: " << loadResult.description() << endl;

    //Parse spritesheets
    vector<char*> sheetNames;
    pugi::xml_node sheets = doc.first_child().child("spritesheets");

    cout << "Spritesheets: " << endl;

    for(pugi::xml_node node = sheets.first_child(); node; node = node.next_sibling()){
        cout << "Spritesheet " << node.attribute("name").value() << endl;
        char* sheetName = new char[strlen(node.attribute("name").value()) + 1];
        strcpy(sheetName, node.attribute("name").value());
        sheetNames.push_back(sheetName);
    }

    //Allocate textures for sprite sheets.
    textureNames = new char*[sheetNames.size()];
    textures = new SDL_Texture*[sheetNames.size()];

    //Load sheet textures.
    for(unsigned int i = 0; i < sheetNames.size(); i++){

        //SDL_RWops *rwop;
        //rwop=SDL_RWFromFile(sheetNames.at(i), "rb");
        SDL_Surface* textureSurface = IMG_Load(sheetNames.at(i));//IMG_LoadPNG_RW(rwop);

        if(!textureSurface){
            cout << "Failed to load image: '" << sheetNames.at(i) << "'. " << IMG_GetError() << endl;
            continue;
        }

        textures[i] = SDL_CreateTextureFromSurface(renderer, textureSurface);
        SDL_FreeSurface(textureSurface);

        textureNames[i] = sheetNames.at(i);
    }
    sheetCount = sheetNames.size();

    //Parse sprites
    pugi::xml_node spritesNodes = doc.first_child().child("sprites");
    vector<BaseSprite*> spritesList;
    vector<char*> namesList;
    vector<pugi::xml_node> nonstaticNodes;

    vector<SpriteSet*> setsList;
    vector<char*> setNamesList;

    //Parse static sprite definitions first.
    cout << "Sprites: " << endl;
    for(pugi::xml_node node = spritesNodes.first_child(); node; node = node.next_sibling()){
        if(strcmp(node.name(), "sprite") == 0){

            StaticSprite* sprite = new StaticSprite(getStringIndex(&sheetNames, node.attribute("sheet").value()), spritesList.size(),
                    textures[getStringIndex(&sheetNames, node.attribute("sheet").value())],
                    node.attribute("x").as_int(), node.attribute("y").as_int(),
                    node.attribute("width").as_int(), node.attribute("height").as_int());
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            cout << "Name: " << name << ", Sheet: " << sprite->sheet
                    << ", x: " << sprite->x << ", y: " << sprite->y
                    << ", Width: " << sprite->width << ", Height: " << sprite->height << endl;

            spritesList.push_back(sprite);
            namesList.push_back(name);
        }else{
            //If not static sprite then push to list to deal with later.
            nonstaticNodes.push_back(node);
        }
    }

    //Process non static sprites
    for(unsigned int n = 0; n < nonstaticNodes.size(); n++){
        pugi::xml_node node = nonstaticNodes.at(n);
        if(strcmp(node.name(), "animatedsprite") == 0){//Animated sprite
            vector<SpriteFrame*> frames;
            for(pugi::xml_node frame = node.first_child(); frame; frame = frame.next_sibling()){
                SpriteFrame* spriteframe = new SpriteFrame();
                spriteframe->duration = frame.attribute("duration").as_int();
                spriteframe->index = getStringIndex(&namesList, frame.attribute("sprite").value());
                frames.push_back(spriteframe);
            }
            AnimatedSprite* sprite = new AnimatedSprite(frames.size(), spritesList.size());

            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            //Load sprite frames.
            cout << "Name: " << name << " Frames: " << frames.size() << endl;
            for(unsigned int i = 0; i < frames.size(); i++){
                sprite->frames[i].duration = frames.at(i)->duration;
                sprite->frames[i].index = frames.at(i)->index;
                sprite->frames[i].sprite = spritesList.at(sprite->frames[i].index);
                cout << "Frame: " << i << ", Sprite Index: " << sprite->frames[i].index
                        << ", Duration: " << sprite->frames[i].duration << "ms." << endl;

				delete frames.at(i); //Delete temp frame
            }
			frames.clear();

            sprite->width = sprite->frames[0].sprite->width;
            sprite->height = sprite->frames[0].sprite->height;
            addDynamicSprite(sprite);
            spritesList.push_back(sprite);
            namesList.push_back(name);
        }else if(strcmp(node.name(), "layeredsprite") == 0){//Layered sprite
            vector<BaseSprite*> layers;
            for(pugi::xml_node layer = node.first_child(); layer; layer = layer.next_sibling()){
                layers.push_back(spritesList.at(getStringIndex(&namesList, layer.attribute("sprite").value())));
            }
            LayeredSprite* sprite = new LayeredSprite(layers.size(), spritesList.size());

            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            //Load sprite layers.
            cout << "Name: " << name << endl;
            for(unsigned int i = 0; i < layers.size(); i++){
                sprite->layers[i] = layers.at(i);
                cout << "Layer: " << i << ", Sprite Index: " << sprite->layers[i]->index << endl;
            }
			layers.clear();
            sprite->width = sprite->layers[0]->width;
            sprite->height = sprite->layers[0]->height;
            spritesList.push_back(sprite);
            namesList.push_back(name);
        }
        else if(strcmp(node.name(), "set") == 0){//Set
            vector<BaseSprite*> setSprites;
            for(pugi::xml_node sprite = node.first_child(); sprite; sprite = sprite.next_sibling()){
                setSprites.push_back(spritesList.at(getStringIndex(&namesList, sprite.attribute("name").value())));
            }
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            cout << "Name: " << name << endl;

            //Load set sprites.
            SpriteSet* set = new SpriteSet(setSprites.size());
            for(unsigned int i = 0;i < setSprites.size(); i++){
                set->sprites[i] = setSprites.at(i);
                cout << "Set Sprite: " << i << ", Sprite Index: " << set->sprites[i]->index << endl;
            }
            setsList.push_back(set);

            setNamesList.push_back(name);
        }
    }

    //Copy sprites into sprite array
    spriteCount = spritesList.size();
    sprites = new BaseSprite*[spriteCount];
    for(unsigned int i = 0; i < spriteCount; i++){
        sprites[i] = spritesList.at(i);
    }
	spritesList.clear();

    //Copy sprite names into sprite names array while sorting them by name
    //Simple insertion sort.
    spriteNames = new SpriteNameIndex[spriteCount];
    for(unsigned int i = 0; i < namesList.size(); i++){
        spriteNames[i].name = namesList.at(i);
        spriteNames[i].index = i;
        sprites[i]->name = spriteNames[i].name;

        //Find proper name order for this name.
        int current = i;
        for(int j = i-1; j >= 0; j--){
            if(strcmp(spriteNames[current].name, spriteNames[j].name) < 0){

                char* tmpName = spriteNames[j].name;
                int tmpIndex = spriteNames[j].index;
                spriteNames[j].name = spriteNames[current].name;
                spriteNames[j].index = spriteNames[current].index;

                spriteNames[current].name = tmpName;
                spriteNames[current].index = tmpIndex;

                current--;
            }else{
                break;
            }
        }
    }

    //Copy sprite sets into sprite set array
    spriteSetCount = setsList.size();
    spriteSets = new SpriteSet*[spriteSetCount];
    for(unsigned int i = 0; i < spriteSetCount; i++){
        spriteSets[i] = setsList.at(i);
    }

    //Copy sprite set names into name array while sorting.
    spriteSetNames = new SpriteNameIndex[spriteSetCount];
    for(unsigned int i = 0; i < setNamesList.size(); i++){
        spriteSetNames[i].name = setNamesList.at(i);
        spriteSetNames[i].index = i;

        //Find proper name order for this name.
        int current = i;
        for(int j = i-1; j >= 0; j--){
            if(strcmp(spriteSetNames[current].name, spriteSetNames[j].name) < 0){

                char* tmpName = spriteSetNames[j].name;
                int tmpIndex = spriteSetNames[j].index;
                spriteSetNames[j].name = spriteSetNames[current].name;
                spriteSetNames[j].index = spriteSetNames[current].index;

                spriteSetNames[current].name = tmpName;
                spriteSetNames[current].index = tmpIndex;

                current--;
            }else{
                break;
            }
        }
    }

    delete sourceFile;
}

/**
* Get index of string in vector.
*/
int SpriteManager::getStringIndex(vector<char*>* strings, const char* name){
    for(unsigned int i = 0; i < strings->size(); i++){
        if(strcmp(name, strings->at(i)) == 0){
            return i;
        }
    }
    return NO_SPRITE; //Should crash
}

/**
* Save sprites in manager to file.
* @param file The file name to save to. Do not append file extension.
*/
void SpriteManager::saveSprites(const char* file){

    //Open destination file.
    cout << "Saving sprites" << endl;
    ofstream fileWriter;
    char* destFile = new char[strlen(file) + 5];
    strcpy(destFile, file);
    strcat(destFile, ".dat");
    fileWriter.open(destFile, ios::binary | ios::out);
    if(fileWriter.fail()){
        cout << "Open file failed." << endl;
        delete destFile;
        return;
    }

    //Write sheet definitions
    fileWriter.write((char*) &sheetCount, sizeof(sheetCount));
    for(int i = 0; i < sheetCount; i++){
        unsigned char nameLen = strlen(textureNames[i]);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(textureNames[i], nameLen);
    }

    //Write all sprites.
    fileWriter.write((char*) &spriteCount, sizeof(spriteCount));
    for(int i = 0; i < spriteCount; i++){
        if(sprites[i]->type == BaseSprite::st_Static){
            StaticSprite* sprite = (StaticSprite*) sprites[i];
            unsigned char type = 0;
            fileWriter.write((char*) &type, sizeof(type));
            fileWriter.write((char*) &sprites[i]->sheet, sizeof(sprites[i]->sheet));
            fileWriter.write((char*) &sprite->x, sizeof(sprite->x));
            fileWriter.write((char*) &sprite->y, sizeof(sprite->y));
            fileWriter.write((char*) &sprite->width, sizeof(sprite->width));
            fileWriter.write((char*) &sprite->height, sizeof(sprite->height));
        }else if(sprites[i]->type == BaseSprite::st_Animated){
            AnimatedSprite* animatedSprite = (AnimatedSprite*) sprites[i];
            unsigned char type = 1;
            fileWriter.write((char*) &type, sizeof(type));
            fileWriter.write((char*) &animatedSprite->frameCount, sizeof(animatedSprite->frameCount));
            for(int f = 0; f < animatedSprite->frameCount; f++){
                fileWriter.write((char*) &animatedSprite->frames[f].index, sizeof(animatedSprite->frames[f].index));
                fileWriter.write((char*) &animatedSprite->frames[f].duration, sizeof(animatedSprite->frames[f].duration));
            }
        }else if(sprites[i]->type == BaseSprite::st_Layered){
            LayeredSprite* layeredSprite = (LayeredSprite*) sprites[i];
            unsigned char type = 2;
            fileWriter.write((char*) &type, sizeof(type));
            fileWriter.write((char*) &layeredSprite->layerCount, sizeof(layeredSprite->layerCount));
            for(int l = 0; l < layeredSprite->layerCount; l++){
                fileWriter.write((char*) &layeredSprite->layers[l]->index, sizeof(layeredSprite->layers[l]->index));
            }
        }
    }

    //Write sprite name index.
    for(int i = 0; i < spriteCount; i++){
        fileWriter.write((char*) &spriteNames[i].index, sizeof(spriteNames[i].index));
        unsigned char nameLen = strlen(spriteNames[i].name);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(spriteNames[i].name, nameLen);
    }

    //Write sprite sets
    fileWriter.write((char*) &spriteSetCount, sizeof(spriteSetCount));
    for(int i = 0; i < spriteSetCount; i++){
        fileWriter.write((char*) &spriteSets[i]->numSprites, sizeof(spriteSets[i]->numSprites));
        for(int j = 0; j < spriteSets[i]->numSprites; j++){
            fileWriter.write((char*) &spriteSets[i]->sprites[j]->index, sizeof(spriteSets[i]->sprites[j]->index));
        }
    }

    //Write sprite set name index
    for(int i = 0; i < spriteSetCount; i++){
        fileWriter.write((char*) &spriteSetNames[i].index, sizeof(spriteSetNames[i].index));
        unsigned char nameLen = strlen(spriteSetNames[i].name);
        fileWriter.write((char*) &nameLen, sizeof(nameLen));
        fileWriter.write(spriteSetNames[i].name, nameLen);
    }

    fileWriter.close();
    delete destFile;
}


/**
* Get sprite by name.
*/
BaseSprite* SpriteManager::getSprite(const char* name){
    int index = getSpriteIndex(name);
    if(index != NO_SPRITE)
        return sprites[index];
    else
        return 0;
}

/**
* Find index by name in a SpriteNameIndex list. Binary search of sorted list.
*/
unsigned short SpriteManager::findName(SpriteNameIndex* list, unsigned short listSize, const char* name){
    int index = listSize/2;
    int lastIndex = -1;
    int size = listSize/2;
    while(true){
        if(size != 1)
            size =size/2;//Halve the search target size.

        int comp = strcmp(name, list[index].name);

        if(comp == 0){ //Found sprite.
            return list[index].index;
        }else if(comp > 0){
            index+=size;
        }else if(comp < 0){
            index-=size;
        }

        if(index < 0)
            index = 0;
        else if(index >= listSize)
            index = listSize - 1;

        if(index == lastIndex) //Reached expected location with no match
            break;

        lastIndex = index;
    }
    return NO_SPRITE;
}

/**
* Get sprite index in sprite list by name.
*/
unsigned short SpriteManager::getSpriteIndex(const char* name){
    return findName(spriteNames, spriteCount, name);
}

/**
* Get sprite set by name.
*/
SpriteSet* SpriteManager::getSpriteSet(const char* name){
    return spriteSets[findName(spriteSetNames, spriteSetCount, name)];
}

/**
* Clear all sprites and textures from memory.
*/
SpriteManager::~SpriteManager(){

    dynamicList.clear();

    //Clear sprite definitions
    for(int i = 0; i < spriteCount; i++){
        delete sprites[i];
		delete spriteNames[i].name;
		spriteNames[i].name = 0;
        sprites[i] = 0;
    }
    delete sprites;
    sprites = 0;

    delete spriteNames;
    spriteNames = 0;

    //Clear sprite set definitions
    for(int i = 0; i < spriteSetCount; i++){
        delete spriteSets[i];
		delete spriteSetNames[i].name;
        spriteSets[i] = 0;
    }
    delete spriteSets;
    spriteSets = 0;

    delete spriteSetNames;
    spriteSetNames = 0;

    //Clear texture names
    for(int i = 0; i < sheetCount; i++){
        delete textureNames[i];
        textureNames[i] = 0;
    }

	delete textureNames;
	textureNames = 0;

}
