#include <Engine.h>

#include <thread>
#include <chrono>
#include <limits>

#include <core/systems/EngineSystem.h>
#include <core/components/EngineComponents.h>

namespace Sopel {

std::string Engine::VERSION = "0.011";

Engine::Engine(uint16 width, uint16 height, std::string name)
    : IEntitiesManager ()
    , IComponentsManager ()
    , _utilities {this, this, this}
{
    _window = Window::CreateWindow(width, height, name);
    _renderer = std::make_unique<OGL>(_window->getProcAddress());
}

void Engine::init()
{
    registerSystem(ENGINE_SYSTEMS::RENDER_SYSTEM, sysRenderer, 10u, ((1<<CRender::ID) | (1<<CWorldTransform::ID)));
    gameInit();
}

int Engine::start()
{
    Sopel::time_point frameTime = std::chrono::steady_clock::now();
    Sopel::time_point lastFrameTime = std::chrono::steady_clock::now();

    float frameDeltaTime = .0f;
    float maxFrameTime = std::numeric_limits<double>::min();
    float minFrameTime = std::numeric_limits<double>::max();
    
    uint64 frameCount = 0u;
    double gameTime = .0;

    bool first10Frame = true;   

    while(!_window->shouldClose()) 
    {
        std::cout << "============= Start =============" << std::endl;
        // Calculate frame time informations
        frameTime = std::chrono::steady_clock::now();
        frameDeltaTime = std::chrono::duration<float, std::milli>(frameTime - lastFrameTime).count();
        lastFrameTime = frameTime;

        gameTime += frameDeltaTime;
        frameCount += 1;
        
        if((frameDeltaTime > maxFrameTime) && (!first10Frame)) {maxFrameTime = frameDeltaTime;}
        if((frameDeltaTime < minFrameTime) && (!first10Frame)) {minFrameTime = frameDeltaTime;}

        _renderer->startFrame(0);
        _window->update();
        
        for(auto system : getSystems()) {
            if(system.enable) {
                system.fun(getMatch(system.key), frameDeltaTime, _utilities);
            }
        }

        if(frameCount == DISCARD_FIRST_N_FRAMES) {first10Frame = false;};
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "============== End ==============" << std::endl;
        if(frameCount > 7) { 
            auto system = getSystem(ENGINE_SYSTEMS::RENDER_SYSTEM);
            if(nullptr != system) {
                system->enable = true;
            }
            else {
                std::cout << "Error getting ENGINE_SYSTEMS::RENDER_SYSTEM " << std::endl;
            }
        } 
        if(frameCount > 10) { 
            auto system = getSystem(ENGINE_SYSTEMS::RENDER_SYSTEM);
            if(nullptr != system) {
                system->enable = false;
            }
            else {
                std::cout << "Error getting ENGINE_SYSTEMS::RENDER_SYSTEM " << std::endl;
            }
        } 
    }

    double avgFrameTime = gameTime / frameCount;
    std::cout << "Performance informations:" << std::endl
              << "  min time: " << minFrameTime << std::endl
              << "  avg time: " << avgFrameTime << std::endl
              << "  max time: " << maxFrameTime << std::endl
              << std::endl;
    return 0;
}

std::string Engine::printVersion()
{
    return VERSION;
}

};