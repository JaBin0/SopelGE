#include <iostream>

#include <core/systems/ISystemsManager.h>


namespace Sopel {

void ISystemsManager::registerSystem(SYSID sysId, SystemFun sysFunction, uint32 sysPriority, EKEY sysKey) {
    // Insert system at the back and swap it with proper element if needed 
    _systems.push_back({sysId, sysFunction, sysPriority, sysKey, true});

    for (auto sysIt = _systems.begin() ; sysIt != _systems.end(); ++sysIt) {
        if(sysPriority < sysIt->priority ) {
            std::rotate(sysIt, _systems.end() - 1, _systems.end());
            break;
        }
    }
}

void ISystemsManager::printRegisteredSystem() {
    std::cout << "Systems: ";
    for(auto system : _systems) {
        std::cout << "{Id: "<< system.id << ", Prio: " << system.priority << "}, ";
    }
    std::cout << std::endl;
}

const Systems& ISystemsManager::getSystems() {
    return _systems;
}

System* ISystemsManager::getSystem(const SYSID id) {
    System* system = nullptr;
    for (System& sys : _systems) {
        if(id == sys.id) {
            system = &sys;
            break;
        }
    }
    return system;
}

bool ISystemsManager::runSystem(SYSID id) {
    return true;
}

};

