#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <engine/common/BasicTypes.h>

#include <engine/core/components/IComponentsManager.h>
#include <engine/core/entities/IEntitiesManager.h>

#include <WindowOGL.h>
#include <OGL.h>


namespace Sopel {

class Engine 
    : public IEntitiesManager
    , public IComponentsManager 
{
public: 
    /*! \brief Constructors && Destructor */
    Engine() = delete;
    Engine(uint16 width, uint16 height, std::string name);

    /*! \brief Initialize engine */
    void init();

    /*! \brief User defined initialize method for the game elements */
    virtual void gameInit() = 0;

    /*! \brief User defined initialize method for the engine elements like registreing systems, render pipline etc. */
    virtual void userEngineInit() = 0;

    /*! \brief Print engine version */
    virtual std::string printVersion();
    
    /*! \brief Start main loop of the engine */
    int start();

protected:
    /*! \brief Engine renderer handle */
    std::unique_ptr<Sopel::IRenderer> _renderer;

    /*! \brief Engine window handle*/
    std::unique_ptr<Sopel::Window> _window;

public:
    static std::string VERSION;
};

};