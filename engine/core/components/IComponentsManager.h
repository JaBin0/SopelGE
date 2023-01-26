#pragma once
#include <iostream>

#include <engine/core/entities/Entity.h>
#include <engine/core/components/Component.h>

namespace Sopel {
class IComponentsManager {
public:
    /*! \brief Add component to the entity 
     * After adding new component it is possible that the whole storage can be moved therefore
     * consider previous pointers to the components of this type invalidated. Moving storage 
     * will also update pointers stored by entity. 
     *    TODO! Instead of returning raw pointer, return wrapper/handler which will be always up to date 
     */
    template <class T>
    T* addComponent(Entity& entity);

    /*! \brief 
     * 
     */
    template <class T>
    T* getComponent(Entity& entity);

    /*! \brief Print content of component storage manager */
    template <class T>
    void printCSM();

private:
    /*! \brief Default size of the single component storage */
    static const uint32 DEFAULT_COMPONENT_STORAGE_SIZE = 64u;

    /*! \brief Stores all components register within the system */
    Components _components;

};

template <class T>
T* IComponentsManager::addComponent(Entity& entity)
{
    if (0 == _components.count(T::ID)) {
        _components.insert({T::ID, {}});
        _components.at(T::ID).data.resize(DEFAULT_COMPONENT_STORAGE_SIZE);
    }
    
    T* component = nullptr;
    if(entity.checkKey(1<<T::ID)) 
    {
        return getComponent<T>(entity);
    }
    
    auto& csm = _components.at(T::ID);
    if(csm.next >= csm.data.size()) {
        csm.data.resize(csm.data.size() + (DEFAULT_COMPONENT_STORAGE_SIZE));
        // for (auto& ent : _entities) {
        // //     if(ent.checkKey(1 << T::ID)) {
        // //         uint64 pos = ent.getComponentPos<T>();
        // //         BasicComponent* newAddress = reinterpret_cast<BasicComponent*>(&csm.data.at(pos));
        // //         ent.updateComponnentAddr<T>(newAddress);
        // //     }
        // }
    }

    component = new(&csm.data.at(csm.next))T();
    entity.linkComponent(T::ID, component, csm.next);
    csm.next += T::SIZE;

    return component;
}

template <class T>
T* IComponentsManager::getComponent(Entity& entity) {
    if(!entity.checkKey(1<<T::ID)) {
        return nullptr;
    }

    uint8* component = &_components.at(T::ID).data.at(entity.getComponentPos<T>());
    return reinterpret_cast<T*>(component);
}

template <class T>
void IComponentsManager::printCSM() {
    std::cout << "Print CSM <" << T::ID << ">: " << std::endl;
    auto& csmData = _components.at(T::ID).data;
    for(uint8 value : csmData) {
        std::cout << std::dec << static_cast<uint16_t>(value) << ", ";
    }
    std::cout << std::endl;
}
};