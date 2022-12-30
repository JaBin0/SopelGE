#include <iostream>
#include <iomanip>

#include "IEntitiesManager.h"

namespace Sopel {

IEntitiesManager::IEntitiesManager() 
    : _entities {}
    , _lastId {-1u}
{
    _entities.reserve(100);
}

Entity& IEntitiesManager::addEntity(std::string name) {
    EID id = findUniqueId();
    _entities.push_back(Entity(id, name)); 
    return _entities.back();
}

const EID IEntitiesManager::findUniqueId() {
    EID next = _lastId + 1;
    bool uniqueFound = true;
    do {
        uniqueFound = true;
        for (auto entity : _entities) {
            if(entity.id() == next) {
                ++next;
                uniqueFound = false;
                break; 
            }
        }
    }
    while (!uniqueFound);
    return next;
}

void IEntitiesManager::printEntities() const {
    for(Entity entity : _entities) {
        std::cout << "Entity " 
                  << "<" << (entity.alive() ? 'A' : 'D') << "> " 
                  << "[0x" << std::hex << entity.id() << std::dec << "] " 
                  << std::setfill(' ') << std::setw(10) << entity.name().data() << " " 
                  << "key: " << entity.key() 
                  << std::endl;
    }
}

EntitiesRef IEntitiesManager::getMatch(EKEY entityKey) {
    EntitiesRef matchedEntity;
    for(Entity& entity : _entities) {
        if(entity.checkKey(entityKey)) {
            matchedEntity.push_back(entity);
        }
    }
   return matchedEntity;
}

};



