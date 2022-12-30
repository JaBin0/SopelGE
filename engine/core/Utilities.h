#pragma once
// #include <core/systems/ISystemsManager.h>
// #include <core/entities/IEntitiesManager.h>
// #include <core/components/IComponentsManager.h>

namespace Sopel {

class ISystemsManager;
class IEntitiesManager;
class IComponentsManager;

struct Utilities {
    /*! \brief */
    ISystemsManager* const systemsMgr = nullptr;

    /*! \brief */
    IEntitiesManager* const entitiesMgr = nullptr;

    /*! \brief */
    IComponentsManager* const componentsMgr = nullptr;
};

};