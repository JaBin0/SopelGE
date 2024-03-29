#pragma once
#include <entities/Entity.h>

namespace Sopel {
/*! \brief Class responsible for managing entities within engine. */
class IEntitiesManager {
public:
    IEntitiesManager();

    /*! \brief Register new entity within a system and return handler to newly added element 
     * \param name - Name of the entity, can be used to identify specific entities 
     */
    Entity& addEntity(std::string name = "");

    /*! \brief Find next unique entity id */
    const EID findUniqueId();

    /*! \brief */
    EntitiesRef getMatch(EKEY entityKey);

    /*! \brief Print all entities currently registered within the engine */
    void printEntities() const;

private:
    /*! \brief Stores all entities register within the system */
    Entities _entities;

    /*! \brief Last id assign to the newly added entity. Used as a start value for finding unique id and help spread ids across whole possible values */
    EID _lastId;
};
};