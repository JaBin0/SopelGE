#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <limits>

#include <engine/common/Types.h>

#include <engine/core/Utilities.h>

#include <engine/core/components/IComponentsManager.h>
#include <engine/core/entities/IEntitiesManager.h>
#include <engine/core/systems/ISystemsManager.h>
#include <engine/assets/IAssetsManager.h>



#include <WindowOGL.h>
#include <OGL.h>


namespace Sopel {

#define DISCARD_FIRST_N_FRAMES 10u

class Engine 
    : public IEntitiesManager
    , public IComponentsManager
    , public ISystemsManager
    , public IAssetsManager 
{
public: 
    /*! \brief Constructors && Destructor */
    Engine() = delete;
    Engine(uint16 width, uint16 height, std::string name);

    /*! \brief Initialize engine */
    void init();

    /*! \brief User defined initialize method for the game elements */
    virtual void gameInit() = 0;

    /*! \brief User defined initialize method for the engine elements like registering systems, render pipeline etc. */
    virtual void userEngineInit() = 0;

    AssetID registerModel(const std::string filePath);

    AssetID registerImage(const std::string imgPath);

    /**! \brief */
    void registerGraphicPipeline(const GPID id, const std::string vertexShader, const std::string fragmentShader);

    /*! \brief Print engine version */
    virtual std::string printVersion();



    /*! \brief Start main loop of the engine */
    int start();

private:

protected:
    /*! \brief Engine renderer handle */
    std::shared_ptr<Sopel::IRenderer> _renderer;

    /*! \brief Engine window handle*/
    std::unique_ptr<Sopel::Window> _window;

    /*! \brief Limit number of frame per seconds, float used so for the debug reason it can be set to for example 0.25 fps*/
    float _maxfps = std::numeric_limits<float>::min();

private:

    /*! \brief */
    struct Utilities _utilities;
    // /*! \brief */
    // struct Utilities _utilities;
    // /*! \brief */
    // Systems _systems;

public:
    static std::string VERSION;
};

};