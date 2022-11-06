#include <Engine.h>

namespace Sopel {

std::string Engine::VERSION = "0.011";

Engine::Engine(uint16 width, uint16 height, std::string name)
{
    _window = Window::CreateWindow(width, height, name);
    _renderer = std::make_unique<OGL>(_window->getProcAddress());
}

int Engine::start()
{
    while(!_window->shouldClose()) 
    {
        _renderer->startFrame(0);
        _window->update();
    }
    return 0;
}

std::string Engine::printVersion()
{
    return VERSION;
}

};