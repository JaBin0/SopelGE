#pragma once
#include <systems/System.h>

namespace Sopel {

/*! \brief */
class ISystemsManager {
public:

    /*! \brief */
    System* getSystem(SYSID id);

    /*! \brief */
    bool runSystem(SYSID id);

protected: 
    /*! \brief */
    const Systems& getSystems();

    /*! \brief */
    void registerSystem(SYSID sysId, SystemFun sysFunction, uint32 sysPriority, EKEY sysKey);

    /*! \brief */
    void printRegisteredSystem();

private:
    Systems _systems;
};

};