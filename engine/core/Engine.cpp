#include <Engine.h>

#include <thread>
#include <chrono>


#include <core/systems/EngineSystem.h>
#include <core/components/EngineComponents.h>

#include <engine/assets/Model.h>

using namespace std::chrono_literals;

namespace Sopel {

std::string Engine::VERSION = "0.011";

Engine::Engine(uint16 width, uint16 height, std::string name)
    : IEntitiesManager ()
    , IComponentsManager ()
{
    _window = Window::CreateWindow(width, height, name);
    _renderer = std::make_shared<OGL>(_window->getProcAddress(), width, height);
    _utilities = {this, this, this, _renderer.get()};
}

void Engine::init()
{
    registerSystem(ENGINE_SYSTEMS::RENDER_SYSTEM, sysRenderer, 10u, ((1<<CRender::ID) | (1<<CWorldTransform::ID)));
    
    _renderer->registerGraphicPipeline(1, "assets/shaders/point.vert", "assets/shaders/point.frag");
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

        //std::cout << "============= Start =============" << std::endl;
        _window->pollEvents();
        _renderer->startFrame(0);

        // Calculate frame time informations
        frameTime = std::chrono::steady_clock::now();
        frameDeltaTime = std::chrono::duration<float, std::milli>(frameTime - lastFrameTime).count();
        lastFrameTime = frameTime;

        gameTime += frameDeltaTime;
        frameCount += 1;

        if(first10Frame && frameCount > 10) {first10Frame = false;} 
        if((frameDeltaTime > maxFrameTime) && (!first10Frame)) {maxFrameTime = frameDeltaTime;}
        if((frameDeltaTime < minFrameTime) && (!first10Frame)) {minFrameTime = frameDeltaTime;}

        float time = std::chrono::time_point_cast<std::chrono::milliseconds>(frameTime).time_since_epoch().count() / 1000.f;
        _renderer->setTime(time);
        
        for(auto system : getSystems()) {
            if(system.enable) {
                system.fun(getMatch(system.key), frameDeltaTime, _utilities);
            }
        }
        _window->update();
        
        if(_maxfps > std::numeric_limits<float>::min()) {
            float executionTime = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - frameTime).count();
            //std::cout << "Frame execution time: " << executionTime << std::endl;
            auto msPerFrame = std::chrono::duration<float, std::milli>(1s).count() / _maxfps; 
            std::cout << "ms per frame: " << msPerFrame << std::endl;
            std::cout << "Sleep for: " << std::chrono::duration<float, std::milli>(msPerFrame - executionTime).count() << std::endl;
            std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(msPerFrame - executionTime));
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(200));
       // std::cout << "============== End ==============" << std::endl;
    }

    double avgFrameTime = gameTime / frameCount;
    std::cout << "Performance informations:" << std::endl
              << "  min time: " << minFrameTime << std::endl
              << "  avg time: " << avgFrameTime << std::endl
              << "  max time: " << maxFrameTime << std::endl
              << std::endl;
    return 0;
}

AssetID Engine::registerModel(const std::string filePath) {
    std::cout << "Registering model <" << filePath.data() << "> .... ";
    auto [id, model] = loadModelAsset(filePath);
    if(id == INVALID_ASSET_ID) {
        return INVALID_ASSET_ID;
    }

    if(!_renderer->registerMesh(id, model->mesh)) {
        return INVALID_ASSET_ID;
    }

    std::cout << "Success" << std::endl;
    return id;  
}

std::string Engine::printVersion()
{
    return VERSION;
}

};