// System headers
#include <iostream>
// Own headers
#include <engine/graphic/OGL.h>

namespace Sopel {

OGL::OGL(GLADloadproc procAddress)
{
    
    
    int success = gladLoadGLLoader((GLADloadproc)procAddress);
    if(!success) {
        std::cout << "OpenGL function poiters could not be retrive by GLAD" << std::endl;        
    }
    glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
}

ErrorCodes::value OGL::registerModel(AssetId id, const Model& model)
{
    
    return ErrorCodes::_NO_ERROR;
}

void OGL::draw() 
{
    glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

};

