#pragma once
// #include <core/systems/ISystemsManager.h>
// #include <core/entities/IEntitiesManager.h>
// #include <core/components/IComponentsManager.h>

namespace Sopel {

class ISystemsManager;
class IEntitiesManager;
class IComponentsManager;
class IRenderer;

struct Utilities {
    /*! \brief */
    ISystemsManager* systemsMgr = nullptr;

    /*! \brief */
    IEntitiesManager* entitiesMgr = nullptr;

    /*! \brief */
    IComponentsManager* componentsMgr = nullptr;

    /*! \brief */
    IRenderer* renderer = nullptr;
};

};