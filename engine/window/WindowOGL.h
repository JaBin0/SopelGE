#pragma once
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <common/BasicTypes.h>

namespace Sopel {


/** Class representing Sopel engine window based on the GLFW.    
 * 
*/
class Window {
public:
    //
    static std::unique_ptr<Window> CreateWindow(uint16 width, uint16 height, std::string windowName);
    bool isInitialized();

    bool shouldClose();
    void update();
    void pollEvents();

    GLADloadfunc getProcAddress();

    ~Window();
protected:
    Window() = delete;
    Window(uint16 width, uint16 height, std::string windowName);
    bool _initialized;    
    GLFWwindow* _window;
}; 
}

/*
    glfwInit();

    _window = glfwCreateWindow(1280, 720, "Hello", NULL, NULL);
    if(!_window) {
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);
}

void SGELevelEditor::run()
{
    std::cout << "Start program" << std::endl;
    while(!glfwWindowShouldClose(_window))
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    glfwDestroyWindow(_window);
    glfwTerminate();

*/