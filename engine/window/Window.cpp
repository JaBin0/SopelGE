// System headers
#include <iostream>

// External headers
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Own headers
#include <Window.h>

/*
 std::cout << "SopelGE::Window" << std::endl;



    _window = glfwCreateWindow(width, height, windowName.data(), NULL, NULL);
    if(!_window) {
        glfwTerminate();
        std::cout << "SopelGE::Window::ERROR: Window could not be created correctly" << std::endl;  
        return;
    }

    glfwMakeContextCurrent(_window);
    _initialized = true;
*/

namespace Sopel {

Window::Window() 
    : _window(nullptr, [](GLFWwindow* ptr){if(nullptr != ptr) {glfwDestroyWindow(ptr);}})
{ 
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if(!glfwInit()) {std::cout << "ERROR [Window] GLFW could not been initialized" << std::endl; return;}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window.reset(glfwCreateWindow(800,600, "Test", nullptr, nullptr));
     if(!_window) {
        std::cout << "ERROR [Window] - GLFW window was not created" << std::endl;
        return;
    }
    glfwMakeContextCurrent(_window.get());
}   

Window::~Window() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Window::init() {
    std::cout << "Window init" << std::endl;
    glfwSetWindowSize(_window.get(), 1600, 400);
}

bool Window::closeSignal() {
    return glfwWindowShouldClose(_window.get());
}

void Window::update() {
    glfwSwapBuffers(_window.get());
    glfwPollEvents();
}

};