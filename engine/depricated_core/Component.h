#pragma once
// System headers
#include <unordered_map>
// Own headers
#include <engine/core/types.h>

/* Define type of the component ID and therefore the maximum number of the defined component types*/
using CID = uint16;

/*! Define type for the component map which allow to reinterpret blob of bytes into specific components */
using CMap = std::unordered_map<CID, uint32>;

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
struct BaseComponent : private BasicComponent
{
    static CID ID;
};

template <class T>
uint16 BaseComponent<T>::ID (BasicComponent::nextID());

/* Define macro for creation of the new components */
#define _COMPONENT(componentName) struct componentName : public Sopel::BaseComponent<componentName>

};