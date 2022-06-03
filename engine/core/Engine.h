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

// Forward declaration
class GLFWwindow;

namespace Sopel {
// Defines
#define VERSION 0.002

class Engine {
public:
    Engine();
    virtual ~Engine();

    /** Contains current version of the Game engine. */
    static const float version;

    /** Register model within engine system and return assign id */
    AssetId registerModel(std::string path);

    /** Start main loop of the game */
    void start();

protected:
    /** Indicate that the engine was initialize successfully*/
    bool m_initialized;

    /** Instance of the assets manager */
    std::shared_ptr<IAssetsManager> m_iAssetsMgr;

    /** Instance of the renderer */
    std::shared_ptr<IRenderer> m_iRenderer;

    /** Instance of window */
    GLFWwindow* m_window;
};};