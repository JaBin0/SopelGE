// System haeaders
#include <string>
// Own headers
#include <engine/core/Engine.h>
#include <engine/graphic/OGL.h>
#include <engine/assets/AssimpAssetsManager.h>





namespace Sopel {
// Static variables
const float Engine::version = 0.001f;

Engine::Engine() 
    : m_iAssetsMgr{std::make_shared<AssimpAssetsManager>()}
    , m_iRenderer{std::make_shared<OGL>()}
{
}

Engine::~Engine() 
{

}

AssetId Engine::registerModel(const std::string asset)
{
    ErrorCodes::value err;
    AssetId assetId = m_iAssetsMgr->registerModel(asset, err);
    if((ErrorCodes::NO_ERROR == err) && (INVALID_ASSETID != assetId)) {
        // Register model within graphic system
        m_iRenderer->registerModel(assetId, m_iAssetsMgr->getModel(assetId));
    }    
    return assetId;
}

};


    