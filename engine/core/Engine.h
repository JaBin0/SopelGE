#pragma once
#include <string>
#include <memory>

#include <common/BasicTypes.h>
#include <WindowOGL.h>
#include <OGL.h>


namespace Sopel {

class Engine {
public: 
    /*! \brief Constructors && Destructor */
    Engine() = delete;
    Engine(uint16 width, uint16 height, std::string name);

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