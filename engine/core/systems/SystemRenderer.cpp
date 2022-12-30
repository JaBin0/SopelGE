#include <iostream>

#include <core/systems/EngineSystem.h>

namespace Sopel {

_SYSTEM(sysRenderer) {
    std::cout << "=== SYSTEM::RENDERER ===" << std::endl;
    int value = 0; 
    for (auto entity : entities) {
        std::cout << "Name: " << entity.get().name().data() << std::endl;
    }
}



};