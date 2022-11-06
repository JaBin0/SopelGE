#pragma once
#include <engine/core/types.h>
#include <engine/assets/IAssetsManager.h>

#include <memory>

//class IAssetsManager;

namespace SopelGE {

class ECSGameEngine {
public:
    ECSGameEngine();
    virtual ~ECSGameEngine();
    ECSGameEngine& operator=(const ECSGameEngine& game_enigne) = delete;
    ECSGameEngine(const ECSGameEngine& game_enigne) = delete;
    ECSGameEngine& operator=(ECSGameEngine&& game_enigne) = delete;
    ECSGameEngine(ECSGameEngine&& game_enigne) = delete;

    /** Method define by the game to iitialize game specific elements */
    virtual void gameInit() = 0;

    /** Start and controll main game loop */ 
    int start();

    virtual int run() = 0;

protected:
    int loadScene(const std::string scene);

private:
    /** Initialize engine specific elements */
    void init();

    /** Instance of the assets manager */
    std::unique_ptr<IAssetsManager> assetsMgr_;

    /** List of the entites  of the assets manager */
    Entities entities_;
};
}