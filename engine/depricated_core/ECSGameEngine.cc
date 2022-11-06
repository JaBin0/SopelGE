#include <engine/core/ECSGameEngine.h>
#include <engine/assets/AssimpAssetsManager.h>

#include <iostream>

namespace SopelGE {

ECSGameEngine::ECSGameEngine() 
    : assetsMgr_ {nullptr}
{
    assetsMgr_ = std::make_unique<AssimpAssetsManager>();
    std::cout << "ECSGameEngine::ECSGameEngine()" << std::endl;
}

ECSGameEngine::~ECSGameEngine() {
    std::cout << "ECSGameEngine::~ECSGameEngine()" << std::endl;
}

int ECSGameEngine::loadScene(const std::string scene)
{
    std::cout << "Loading <" << scene << "> .... ";
    assetsMgr_->registerScene(scene);
    std::cout << "Success" << std::endl;
    return 0;
}

void ECSGameEngine::init() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    gameInit();
}

int ECSGameEngine::start() {
    init();
    return 0;
}

}