#ifndef _MODULELIST_
#define _MODULELIST_

#include <cstring>
#include <iostream>
#include <vector>
#include "pugixml.hpp"

#include "moduletile.hpp"
#include "module.hpp"

/**
 *
 */
class ModuleList{
public:
    std::vector<Module*> modules;

    ModuleList();
};

#endif
