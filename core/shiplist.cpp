#include "shiplist.hpp"

ShipList::ShipList(){

}

void ShipList::load(SpriteManager* sprites){
    std::cout << "Loading ships" << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file("ships.xml");

    //Iterate all <ship> nodes in ships
	pugi::xml_node shipsNode = doc.first_child();
	for (pugi::xml_node shipNode = shipsNode.first_child(); shipNode; shipNode = shipNode.next_sibling())
    {
        Ship* ship = new Ship();
        ship->name = shipNode.attribute("name").value();
        std::cout << "Ship:\t" << ship->name << std::endl;

        std::cout << "\tSprite:\t" <<  shipNode.attribute("image").value();
        ship->sprite = sprites->getSprite(shipNode.attribute("image").value());

        pugi::xml_node mapNode = shipNode.child("map");
        ship->map.init(mapNode.attribute("width").as_int(), mapNode.attribute("height").as_int());

        for (pugi::xml_node tileNode = mapNode.first_child(); tileNode; tileNode = tileNode.next_sibling())
        {
            ship->map.tiles[tileNode.attribute("x").as_int() + tileNode.attribute("y").as_int()*ship->map.width] = tileNode.attribute("free").as_int();
        }

        ships.push_back(ship);

        std::cout << std::endl;
    }
    std::cout << "Finished loading ships." << std::endl;
}
