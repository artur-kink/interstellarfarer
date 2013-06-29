#ifndef _MODULELIST_
#define _MODULELIST_

#include <cstring>
#include <iostream>
#include <vector>
#include "pugixml.hpp"

#include "moduletile.hpp"
#include "module.hpp"

/**
 * List of available module types.
 */
class ModuleList{
public:
    std::vector<Module*> modules;

    ModuleList();
};

#endif
