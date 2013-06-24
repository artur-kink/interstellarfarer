#include "modulelist.hpp"

ModuleList::ModuleList(){

    std::cout << "Loading modules" << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file("modules.xml");

	pugi::xml_node modulesNode = doc.first_child();
    pugi::xml_node moduleNode = modulesNode.first_child();

    Module* module = new Module();
    module->name = std::string(moduleNode.attribute("name").value());
    std::cout << "Module: " << module->name << std::endl;

}

