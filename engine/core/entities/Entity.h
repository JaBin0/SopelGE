#pragma once
#include <vector>
#include <bitset>

#include <engine/common/BasicTypes.h>
#include <engine/core/components/Component.h>

namespace Sopel {
class Entity;


#ifndef ENTITY_KEY_SIZE
    #define ENTITY_KEY_SIZE 8
#endif


using Entities = std::vector<Entity>;

/*! \brief Define key type */ 
using EKEY = std::bitset<ENTITY_KEY_SIZE>;

/*! \brief Define entity id */ 
using EID = uint32;

class Entity {
public:
    Entity() = delete;
    Entity(const EID id, const std::string name = "");

    /*! \brief Marked entity as dead, and remove it from system during the next cleanup */
    void kill();

    /*! \brief Check if key is compatible with this entity */
    bool checkKey(EKEY key);

    /*! \brief Link component with the entity 
     * \param cmpClassId Id of the Component class that will be linked with entity
     * \param component Pointer to the component
     * \param cmpPlaceInCsm Place of the component first byte within Component storage manager 
    */
    void linkComponent(uint16 cmpClassId, BasicComponent* component, uint64 cmpPlaceInCsm);

    /*! \brief Get pointer to the component which is linked with this entity 
     * \param cmpClassId Id of the Component class that will be linked with entity
     * If component of such class is not linked return nullptr
    */
    BasicComponent* getComponent(uint16 cmpClassId);

    /*! \brief Return pointer handler to the linked component. If component of T type is not linked it will return nullptr;
    */
    template <class T>
    T* getComponent();

    /* Temporary sollution user should not be able to change handler to the component within enity */
    template <class T>
    uint64 getComponentPos() const;

    /* Temporary sollution user should not be able to change handler to the component within enity */
    template <class T>
    void updateComponnentAddr(BasicComponent* newAddress);

public: // Getters
    /*! \brief Return entity id */    
    const EID id() const {return _id;}

    /*! \brief Return entity name */    
    const std::string name() const {return _name;}

    /*! \brief Return entity name */    
    const EKEY key() const {return _key;}

    /*! \brief Return if the entity is alive or dead */
    const bool alive() const {return _alive;};

private:
    /*! \brief Unique id of the entity */
    const EID _id;

    /*! \brief Entity name that can help identify this entity */
    const std::string _name;

    /*! \brief Holds current entity status as alive or dead */
    bool _alive;

    /*! \brief Binary key which define types of components linked to this entity */
    EKEY _key;

    std::unordered_map<CID, std::pair<BasicComponent*, uint64>> _linkedComponents;
};

template <class T>
T* Entity::getComponent()
{
    if (_linkedComponents.count(T::ID) != 0) {
        BasicComponent* component = _linkedComponents.at(T::ID).first;
        return reinterpret_cast<T*>(component);
        // T* component = dynamic_cast<T*>();
    }
    return nullptr;
}

template <class T>
uint64 Entity::getComponentPos() const {
    return (_linkedComponents.count(T::ID) != 0) ? _linkedComponents.at(T::ID).second : -1;
}

template <class T>
void Entity::updateComponnentAddr(BasicComponent* newAddress)
{
    if(_linkedComponents.count(T::ID) != 0) {
        _linkedComponents.at(T::ID).first = newAddress;
    }
}

};