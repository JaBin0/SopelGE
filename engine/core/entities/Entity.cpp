#include "Entity.h"
#include <iostream>

namespace Sopel {

Entity::Entity(EID id, std::string name)
    : _id {id}
    , _key {}
    , _alive {true}
    , _name {name}
{

}

bool Entity::checkKey(EKEY key)
{
    return ((key & _key) == key);
}

void Entity::linkComponent(uint16 cmpClassId, BasicComponent* cmp, uint64 cmpPlaceInCsm)
{
    if(_key.test(cmpClassId)) {
        return;
    }

    _linkedComponents.insert({cmpClassId, {cmp, cmpPlaceInCsm}});
    _key.set(cmpClassId);
}

BasicComponent* Entity::getComponent(uint16 cmpClassId)
{
    BasicComponent* component = nullptr;
    if(_key.test(cmpClassId)) {
        component = _linkedComponents.at(cmpClassId).first;
    }
    return component;
}

void Entity::kill() {
    _alive = false;
}

}