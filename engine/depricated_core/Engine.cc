// System haeaders
#include <string>
#include <chrono>
// External headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Own headers
#include <engine/core/Engine.h>
#include <engine/graphic/OGL.h>
#include <engine/assets/AssimpAssetsManager.h>

namespace Sopel {
// Static variables
const float Engine::version = 0.0023f;

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
    m_iRenderer->registerGraphicPipline(SYSTEM_GRAPHIC_PIPLINES::DEFAULT, "assets//shaders//system//default.vert", "assets//shaders//system//default.frag");

    //m_iRenderer->registerTexture(0, "assets//textures//Sidewalk01_1024x1024.png");

    m_iRenderer->registerFont(SYSTEM_FONT, "assets/fonts/arial.ttf");
    m_iRenderer->activateFont(SYSTEM_FONT);
    
    std::cout << "Test submodules new new" << std::endl;

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
    //std::cout << "Loading model: " << asset.data() << " ... ";
    ErrorCodes::value err;
    AssetId assetId = m_iAssetsMgr->registerModel(asset, err);
    if((ErrorCodes::_NO_ERROR == err) && (INVALID_ASSETID != assetId)) {
        // Register model within graphic system
        m_iRenderer->registerModel(assetId, m_iAssetsMgr->getModel(assetId));
    }    
    return assetId;
}

TextureId Engine::registerTexture(std::string asset) 
{
    std::cout << "Loading texture: " << asset.data() << " ... ";
    ErrorCodes::value err;
    AssetId assetId = m_iAssetsMgr->registerTexture(asset, err);

    if(ErrorCodes::_NO_ERROR != err || INVALID_ASSETID == assetId) {
        std::cout << "Failed" << std::endl
                  << "   Error Code: " << std::hex << err << std::endl;
        return INVALID_ASSETID;
    }

    err = m_iRenderer->registerTexture(assetId, m_iAssetsMgr->getTexture(assetId));
    if(ErrorCodes::_NO_ERROR != err) {
        std::cout << "Failed" << std::endl
                  << "   Error Code: " << std::hex << err << std::endl;
        return INVALID_ASSETID;
    }

    std::cout << "Success" << std::endl;
    return assetId;
}


void Engine::start()
{
    if(!m_initialized) {
        std::cout << "ERROR: Engine is not properly initialized" << std::endl;
        return;
    }

    //std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    double time = 0.0f;
    while(!glfwWindowShouldClose(m_window)) {
        //std::chrono::steady_clock::time_point frameTime = std::chrono::steady_clock::now();
    
        //std::chrono::duration<double> timeFromStart = frameTime - startTime;
        //std::chrono::duration<double, std::milli>(timeFromStart).count()

        glfwPollEvents();
        m_iRenderer->startFrame(time);

        for (auto gobject : m_objects) {
            m_iRenderer->draw(gobject);
        }
        // Color color1;
        // color1.values = {111, 190, 124, 23};
        // m_iRenderer->drawText2D("abcdefghijk\nlmnoprstuwxyz", 400, 240, {-0.55f, 2.125f, -0.52f, 2.88f});
        // m_iRenderer->drawText2D("ABCDEFGHIJKL\nMNOPRSTUWXYZ", 400, 400, {0x0000FF4F});
        // m_iRenderer->drawText2D("0123\n456\n789", 300, 120, {232u, 128u, 231u, 182u});
     
        //""
        glfwSwapBuffers(m_window);
        time += 0.007f;
        //int a;
       // std::cin >> a;
    }

}

};


    