#pragma once
// System headers
#include <string>
#include <memory>
#include <iostream>

// Own headers
#include <engine/core/types.h>
#include <engine/errors/ErrorCodes.h>
#include <engine/graphic/IRenderer.h>
#include <engine/assets/IAssetsManager.h>


namespace Sopel {
// Defines
#define VERSION 0.001

class Engine {
public:
    Engine();
    virtual ~Engine();

    /** Contains current version of the Game engine. */
    static const float version;

    /** Register model within engine system and return assign id */
    AssetId registerModel(std::string path);

protected:
    /** Instance of the assets manager */
    std::shared_ptr<IAssetsManager> m_iAssetsMgr;

    /** Instance of the renderer */
    std::shared_ptr<IRenderer> m_iRenderer;
};};