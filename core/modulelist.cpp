#include "modulelist.hpp"


ModuleList::ModuleList(){

}

/**
 * Initialize module list by loading all module definitions in
 * modules.xml
 */
void ModuleList::load(SpriteManager* sprites){
    std::cout << "Loading modules" << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file("modules.xml");

    //Iterate all <module> nodes in modules
	pugi::xml_node modulesNode = doc.first_child();
	for (pugi::xml_node moduleNode = modulesNode.first_child(); moduleNode; moduleNode = moduleNode.next_sibling())
    {
        Module* module = new Module();
        modules.push_back(module);

        module->name = moduleNode.attribute("name").value();
        std::cout << "Module: " << module->name << std::endl;

        std::string hudIcon = moduleNode.attribute("hud_icon").value();
        std::cout << "\tHud Icon: " << hudIcon << std::endl;
        module->hudSprite = sprites->getSprite(hudIcon.c_str());

        std::string storeIcon = moduleNode.attribute("store_icon").value();
        module->storeSprite = sprites->getSprite(storeIcon.c_str());
        std::cout << "\tStore Icon: " << storeIcon << std::endl;

        if(moduleNode.attribute("overlay_icon")){
            std::string overlayIcon = moduleNode.attribute("overlay_icon").value();
            module->overlaySprite = sprites->getSprite(overlayIcon.c_str());
            std::cout << "\tOverlay Icon: " << overlayIcon << std::endl;
        }

        module->health = moduleNode.attribute("health").as_int();
        std::cout << "\tHealth: " << module->health << std::endl;

        module->price = moduleNode.attribute("price").as_int();
        std::cout << "\tPrice: " << module->price << std::endl;

        module->power = moduleNode.attribute("power").as_int();
        std::cout << "\tPower: " << module->power << std::endl;

        //Get module tiles.
        std::cout << "\tTiles:" << std::endl;
        pugi::xml_node tilesNode = moduleNode.child("tiles");
        //Iterate all <tiles> nodes
        for (pugi::xml_node tileNode = tilesNode.first_child(); tileNode; tileNode = tileNode.next_sibling())
        {
            ModuleTile tile;
            tile.x = tileNode.attribute("x").as_int();
            tile.y = tileNode.attribute("y").as_int();
            tile.sprite = sprites->getSprite(tileNode.attribute("image").value());
            module->tiles.push_back(tile);
            std::cout << "\t\tTile\tx: " << tile.x << "\ty: " << tile.y << "\tType: " << tile.type << std::endl;
        }

        module->extension = moduleNode.attribute("extension").as_bool();
        std::cout << "\tExtension: " << module->extension << std::endl;
        module->extendable = moduleNode.attribute("extendable").as_bool();
        std::cout << "\tExtendable: " << module->extendable << std::endl;

        std::cout << std::endl;
    }
    std::cout << "Finished loading modules." << std::endl;
}
