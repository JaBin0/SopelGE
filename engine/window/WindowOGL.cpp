#include <WindowOGL.h>

#include <iostream>

namespace Sopel {

Window::Window(uint16 width, uint16 height, std::string windowName)
    : _initialized {false}
{
    std::cout << "SopelGE::Window" << std::endl;
    if(!glfwInit())
    {
        return;
    }

    _window = glfwCreateWindow(width, height, windowName.data(), NULL, NULL);
    if(!_window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(_window);
    _initialized = true;
}

Window::~Window()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Window::isInitialized()
{
    return _initialized;
}

GLADloadfunc Window::getProcAddress()
{
    return glfwGetProcAddress;
}

std::unique_ptr<Sopel::Window> Window::CreateWindow(uint16 width, uint16 height, std::string windowName)
{
    Window* newWindow = new Window(width, height, windowName);
    return (newWindow->isInitialized()) ? std::unique_ptr<Window>(newWindow) : nullptr;
}

bool Window::shouldClose()
{
    return _initialized ? glfwWindowShouldClose(_window) : true;
}

void Window::update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

};
