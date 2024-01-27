#pragma once
// System headers
#include <functional>
#include <memory>

// Own headers
#include <IWindow.h>

// Forward declaration
class GLFWwindow;

namespace Sopel {

/*! \brief Engine representation of the GLFW window */
class Window : public IWindow {
    /*! \brief Handel to the GLFW window */
    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> _window;

public:
    /*! \brief Constructor && Destructor */
    Window();
    ~Window();

    /*! \brief Initialize Window object. It's decoupled from constructor 
        to postpone whole process, so some settings can be adjusted. 
    */
    void init() override;

    bool closeSignal() override;

    void update() override;
};
};