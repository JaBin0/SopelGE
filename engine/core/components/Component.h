#pragma once
// System headers
#include <unordered_map>
// Own headers
#include <engine/common/BasicTypes.h>

/* Define type of the component ID and therefore the maximum number of the defined component types*/
using CID = uint16;
/* Define type of the component size */
using CSIZE = size_t;

/*! Define type for the component map which allow to reinterpret blob of bytes into specific components */
using CMap = std::unordered_map<CID, uint32>;

/*! Define Component storage manager */
struct ComponentStorageManager {
    uint64 next = 0u;
    std::vector<uint8> data = {};
};

/*! Define type for the components storage */
using Components = std::unordered_map<CID, ComponentStorageManager>;

namespace Sopel {

/* Basic class, which tracks value of the next free CID */
struct BasicComponent 
{
    inline static CID nextID();
};

uint16 BasicComponent::nextID() 
{
    // No protection for number overflow
    static CID id = 0;
    return id++;
};

/* Template for assigning unique ID to the each component */
template <class T>
struct BaseComponent : public BasicComponent
{
    static CID ID;
    static size_t SIZE;
};

template <class T>
CID BaseComponent<T>::ID (BasicComponent::nextID());

template <class T>
size_t BaseComponent<T>::SIZE(sizeof(T));

/* Define macro for creation of the new components */
#define _COMPONENT(componentName) struct componentName : public Sopel::BaseComponent<componentName>

};