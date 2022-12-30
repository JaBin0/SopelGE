#pragma once
#include <functional>
#include <unordered_map>

#include <core/entities/Entity.h>
#include <core/Utilities.h>


namespace Sopel {

/*! \brief TODO! */
struct ENGINE_SYSTEMS {
    enum Value {
        RENDER_SYSTEM = 0u,
        COUNT,
    };
};



/*! \brief System ID */
using SYSID = uint32;

/*! \brief Declaration of the system logic function */
using SystemFun = std::function<void(Sopel::EntitiesRef, const float, struct Sopel::Utilities&)>;  

/*! \brief Declaration of the system logic function */
#define _SYSTEM(Name) void Name (Sopel::EntitiesRef entities, const float deltaTime, struct Sopel::Utilities& tools) 

/*! \brief Sopel system structure */
struct System {
    /*! \brief ID that the systems is registered within engine */
    SYSID id;

    /*! \brief Actual system logic (method) */
    SystemFun fun;

    /*! \brief Priority of the system, which will determine order of the calling */
    uint32 priority;

    /*! \brief System key that will determine which entities will be passed to that system */
    EKEY key;

    /*! \brief Defines if system is currently enabled or disabled. Disabled systems are omit during frame callout */
    bool enable;
};

/*! \brief Sopel system  */
using Systems = std::vector<System>;

};