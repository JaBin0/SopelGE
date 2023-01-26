#include <iostream>
#include <core/components/EngineComponents.h>
#include <core/systems/EngineSystem.h>

namespace Sopel {

_SYSTEM(sysRenderer) {
    //std::cout << "=== SYSTEM::RENDERER ===" << std::endl;
    int value = 0; 
    for (auto entity : entities) {
        CRender* crender = entity.get().getComponent<CRender>();
        if(crender->model != INVALID_ASSET_ID && crender->gpid != INVALID_GP_ID) {
            CWorldTransform* transform = entity.get().getComponent<CWorldTransform>(); 
            tools.renderer->draw(crender->gpid, crender->model, transform->transform);
           // std::cout << "Draw" << std::endl;
        }
        
       
        //std::cout << "Name: " << entity.get().name().data() <<", CRender: " << crender << std::endl;
    }
}



};