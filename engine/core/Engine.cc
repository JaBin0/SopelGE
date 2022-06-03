// System haeaders
#include <string>
// External headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Own headers
#include <engine/core/Engine.h>
#include <engine/graphic/OGL.h>
#include <engine/assets/AssimpAssetsManager.h>

namespace Sopel {
// Static variables
const float Engine::version = 0.001f;

Engine::Engine() 
    : m_initialized{false}
    , m_iAssetsMgr{std::make_shared<AssimpAssetsManager>()}
    , m_iRenderer{}
    , m_window{nullptr}
{
    std::cout << "Initializeing glfw library ... ";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_window = glfwCreateWindow(1280, 720, "Dupa", NULL, NULL);
    if(nullptr == m_window) {
        std::cout << "Failed" << std::endl
                  << "GLFW window could not be created " << std::endl;
        return;
    }
    
    glfwMakeContextCurrent(m_window);
    std::cout << "Success" << std::endl;

    // Renderer need to be crated after glfw context is created
    m_iRenderer = std::make_shared<OGL>((GLADloadproc)glfwGetProcAddress);
    
    


    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glfwSetKeyCallback(m_window, key_callBack);
    // glfwSetScrollCallback(m_window, scroll_callBack);
    // glfwSetCursorPosCallback(m_window, cursor_callBack);
    // glfwSetMouseButtonCallback(m_window, mouse_callBack);
    // glfwSetJoystickCallback(joysctick_callBack);



    // addSupportedKeys();

    // // Get intial sate of the mouse
    // double currentX;
    // double currentY;
    // glfwGetCursorPos(m_window, &currentX, &currentY);
    // mouse.x = currentX;
    // mouse.y = currentY;
    m_initialized = true;
}

Engine::~Engine() 
{

}

AssetId Engine::registerModel(const std::string asset)
{
    ErrorCodes::value err;
    AssetId assetId = m_iAssetsMgr->registerModel(asset, err);
    if((ErrorCodes::_NO_ERROR == err) && (INVALID_ASSETID != assetId)) {
        // Register model within graphic system
        m_iRenderer->registerModel(assetId, m_iAssetsMgr->getModel(assetId));
    }    
    return assetId;
}

void Engine::start()
{
    if(!m_initialized) {
        std::cout << "ERROR: Engine is not properly initialized" << std::endl;
        return;
    }
    
    while(!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        m_iRenderer->draw();

        glfwSwapBuffers(m_window);
    }

}

};


    