// // System headers
// #include <iostream>
#include <fstream>
// // External
// #include <ft2build.h>
// #include FT_FREETYPE_H

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// // Own headers
// #include <engine/core/types.h>
// #include <engine/graphic/OGL.h>
#include <iostream>

#include "OGL.h"

namespace Sopel {

OGL::OGL(GLADloadfunc procAddress) 
    : _time {0.0f}
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    

    int success = gladLoadGL(procAddress);
    if(!success) {
        std::cout << "ERROR: OpenGL function pointers could not be retrieve by GLAD" << std::endl;
        return;        
    }

    _perspective = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f);
    _camera = glm::lookAt(glm::vec3(2.0f, 1.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0));

    glViewport(0, 0, 1280.0f, 720.0f);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void OGL::startFrame(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool OGL::registerMesh(const AssetID assetId, const Mesh& mesh) { 
    uint32 vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float),  mesh.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _meshes.insert({assetId, {vao, vbo, mesh.vertices.size() / 6}});

    return true;
}

bool OGL::registerGraphicPipeline(GPID id, std::string vertexShaderFile, std::string fragmentShaderFile) {
    std::cout << "Registering graphic pipeline [" << id << "]:" << std::endl
              << "    <" << vertexShaderFile.data() <<", " << fragmentShaderFile.data() << "> ... ";
    std::fstream vertexShader, fragmentShader;
    vertexShader.open(vertexShaderFile, std::ios_base::in);
    fragmentShader.open(fragmentShaderFile, std::ios_base::in);
    if(!vertexShader.is_open() || !fragmentShader.is_open()) {
        std::cout << "Failed" << std::endl
                  << "        At least one of the shader source file could not be opened" << std::endl;
        return false;
    }

    std::string content;
    int success;
    char infoLog[512];

    // Create Vertex shader
    std::getline(vertexShader, content, '\0');
    const char* vertexShaderSource = content.data();
    uint16 vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        vertexShader.close();
        fragmentShader.close();
        glDeleteShader(vertexShaderId);
        std::cout << "Failed" << std::endl
                  << "    VERTEX::Info: " << infoLog << std::endl;
        return false;
    }

    // Create Fragment Shader
    content.clear();
    std::getline(fragmentShader, content, '\0');
    const char* fragmentShaderSource = content.data();
    uint16 fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        vertexShader.close();
        fragmentShader.close();
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        std::cout << "Failed" << std::endl
                  << "    FRAGMENT::Info: " << infoLog << std::endl;
    }

    // Create Graphic pipeline
    uint16 graphicPipeline = glCreateProgram();
    glAttachShader(graphicPipeline, vertexShaderId);
    glAttachShader(graphicPipeline, fragmentShaderId);
    glLinkProgram(graphicPipeline);

    glGetProgramiv(graphicPipeline, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(graphicPipeline, 512, NULL, infoLog);
        vertexShader.close();
        fragmentShader.close();
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        glDeleteProgram(graphicPipeline);
        std::cout << "Failed" << std::endl
                  << "   PROGRAM::Info: " << infoLog << std::endl;
        return false;
    }

    _pipelines.insert({id, {graphicPipeline, vertexShaderFile, fragmentShaderFile}});
    std::cout << "Success" << std::endl;
    return true;
}

void OGL::setTime(const float time) {
    _time = time;
}

void OGL::draw(const GPID gpid, const AssetID assetId, const glm::mat4 transform) {
    if( !_pipelines.count(gpid) || !_meshes.count(assetId)) {
        std::cout << "ERROR:DRAW - no gpid <" << gpid <<"> or assetId <" << assetId << "> registered within renderer " << std::endl;
        return; 
    }
    
    GPipeline& pipeline = _pipelines.at(gpid);
    glUseProgram(pipeline.id);

    glUniform1f(glGetUniformLocation(pipeline.id, "time"), _time);

    glUniformMatrix4fv(glGetUniformLocation(pipeline.id, "projection"), 1, GL_FALSE, glm::value_ptr(_perspective));
    glUniformMatrix4fv(glGetUniformLocation(pipeline.id, "view"), 1, GL_FALSE, glm::value_ptr(_camera));
    glUniformMatrix4fv(glGetUniformLocation(pipeline.id, "model"), 1, GL_FALSE, glm::value_ptr(transform));



    const GMesh& mesh = _meshes.at(assetId);
    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.verticesNumber);
}

};
// AssetId m_testId;

// OGL::OGL(GLADloadproc procAddress)
//     : m_graphicPiplines{}
// {
//     int success = gladLoadGLLoader((GLADloadproc)procAddress);
//     if(!success) {
//         std::cout << "OpenGL function poiters could not be retrive by GLAD" << std::endl;        
//     }

//     m_perspective = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f);
//     m_orthographic = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 100.0f);
//     m_camera = glm::lookAt(glm::vec3(1.0f, 2.0f, 12.0f), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0));
//     //m_camera = glm::lookAt(glm::vec3(1.0f, 2.0f, 8.0f), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0));
//     //m_camera = glm::lookAt(glm::vec3(0.0f, 2.0f, 3.5f), glm::vec3(0.0f, 1.5f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0));

//     glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
    
//     // Prepare for drawing text2D 


//     glGenVertexArrays(1, &m_intTextModel.vao);
//     glBindVertexArray(m_intTextModel.vao);
//     glGenBuffers(1, &m_intTextModel.vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, m_intTextModel.vbo);
//     m_intTextModel.verticesNumber = -1;

//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     registerGraphicPipline(SYSTEM_GRAPHIC_PIPLINES::TEXT2D, "assets//shaders//system//text2D.vert", "assets//shaders//system//text2D.frag");

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
//     glEnable(GL_DEPTH_TEST);
        
    
// }

// ErrorCodes::value OGL::registerModel(AssetId id, const Model& model)
// {
//     std::cout << "Register new gModel ... ";
//     uint32 vao;
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);

//     uint32 vbo;
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);

//     vecf data;
//     data.reserve(model.mesh.verticesNumber * model.mesh.vertexSize);
//     for(uint32 vIndex = 0; vIndex < model.mesh.verticesNumber; ++vIndex) {
//         data.push_back(model.mesh.vertices.at(vIndex).x);
//         data.push_back(model.mesh.vertices.at(vIndex).y); 
//         data.push_back(model.mesh.vertices.at(vIndex).z);  

//         data.push_back(model.mesh.textureCoords.at(vIndex).x);
//         data.push_back(model.mesh.textureCoords.at(vIndex).y); 

//         data.push_back(model.mesh.normals.at(vIndex).x);
//         data.push_back(model.mesh.normals.at(vIndex).y); 
//         data.push_back(model.mesh.normals.at(vIndex).z);
//         std::cout << model.mesh.normals.at(vIndex).x << ", " << model.mesh.normals.at(vIndex).y << ", " << model.mesh.normals.at(vIndex).z << "     ";
//         data.push_back(model.mesh.tangents.at(vIndex).x);
//         data.push_back(model.mesh.tangents.at(vIndex).y); 
//         data.push_back(model.mesh.tangents.at(vIndex).z); 
//         std::cout << model.mesh.tangents.at(vIndex).x << ", " << model.mesh.tangents.at(vIndex).y << ", " << model.mesh.tangents.at(vIndex).z << std::endl;
//     }

//     glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)(5 * sizeof(float)));
//     glEnableVertexAttribArray(2);
//     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)(8 * sizeof(float)));
//     glEnableVertexAttribArray(3);
    
//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     m_modelMap.insert({id, {vao, vbo, model.mesh.verticesNumber}});
//     m_testId = id;
//      std::cout << "Success testId: " << m_testId << std::endl;
//     return ErrorCodes::_NO_ERROR;
// }



// ErrorCodes::value OGL::registerFont(FontId id, std::string fontFile) 
// {
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//     std::cout << "Loading font: " << fontFile.data() << " ... ";
//     FT_Library ft;
//     FT_Face face;

//     if(FT_Init_FreeType(&ft) || FT_New_Face(ft, fontFile.data(), 0, &face))
//     {
//         std::cout << "Failed" << std::endl;
//         FT_Done_Face(face);
//         FT_Done_FreeType(ft);
//         return ErrorCodes::LODING_FONT_LIBRARY_FAILED;
//     }

//     m_fonts.insert({id, {}});
//     Font& font = m_fonts.at(id);

//     FT_Set_Pixel_Sizes(face, 0, 48);
//     for(uint16 c = 0; c < 128; c++) {
//         if(!FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//             FT_GlyphSlot& glyph = face->glyph;
//             FT_Bitmap& bitmap = glyph->bitmap;

//             uint32 texture;
//             glGenTextures(1, &texture);
//             glBindTexture(GL_TEXTURE_2D, texture);
//             glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows, 0 , GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
//             Character character = {
//                 texture,
//                 glm::ivec2(bitmap.width, bitmap.rows),
//                 glm::ivec2(glyph->bitmap_left, glyph->bitmap_top),
//                 glyph->advance.x
                
//             };
//             font.insert(std::pair<char, Character>(c, character));
//         }
//     }

//     FT_Done_Face(face);
//     FT_Done_FreeType(ft);

//     std::cout << "Success" << std::endl;
//     return ErrorCodes::_NO_ERROR;
// }

// ErrorCodes::value OGL::registerTexture(AssetId id, const Sopel::Texture& texture)
// {
//     uint32 oglTextureId;
//     glGenTextures(1, &oglTextureId);
//     glBindTexture(GL_TEXTURE_2D, oglTextureId);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0 , GL_RGBA, GL_UNSIGNED_BYTE, texture.data.data());
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     glBindTexture(GL_TEXTURE_2D, 0);
//     m_texturesMap.insert({id, oglTextureId});
//     return ErrorCodes::_NO_ERROR;
// }

// void OGL::startFrame(double time)
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// //     glUseProgram(m_graphicPiplines[0]);
// //     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "projection"), 1, GL_FALSE, glm::value_ptr(m_perspective));
// //     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "view"), 1, GL_FALSE, glm::value_ptr(m_camera));
// //     glUniform1f(glGetUniformLocation(m_graphicPiplines[0], "time"), time);
// }

// void OGL::draw() 
// {
//     glm::mat4 modelMat = glm::mat4(1.0);
//     modelMat = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -10.0f));

//     glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);

//     glUseProgram(m_graphicPiplines[0]);
//     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "projection"), 1, GL_FALSE, glm::value_ptr(m_perspective));
//     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "view"), 1, GL_FALSE, glm::value_ptr(m_camera));
//     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "model"), 1, GL_FALSE, glm::value_ptr(modelMat));

//     struct GModel model = m_modelMap.at(m_testId);
//     glBindVertexArray(model.vao);

//     glDrawArrays(GL_TRIANGLES, 0, model.verticesNumber);
// }

// void OGL::draw(const GObject gobject) 
// {
//     glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "model"), 1, GL_FALSE, glm::value_ptr(gobject.transformation));
//     glUniform4fv(glGetUniformLocation(m_graphicPiplines[0], "baseColor"), 1, glm::value_ptr(gobject.color));
//     glUniform2ui(glGetUniformLocation(m_graphicPiplines[0], "isTextured"), gobject.isTextured ? 1u : 0u, gobject.isNormalMap ? 1u: 0u);
//     if(gobject.isTextured)
//     {
//         glActiveTexture(GL_TEXTURE0);
//         glUniform1i(glGetUniformLocation(m_graphicPiplines[0], "image"), 0);
//         glUniform2fv(glGetUniformLocation(m_graphicPiplines[0], "textureScale"), 1,  glm::value_ptr(gobject.textureScale));
//         //std::cout << "TextureId: " << gobject.textureId << std::endl;
//         glBindTexture(GL_TEXTURE_2D, m_texturesMap.at(gobject.textureId));
//     }
//     if(gobject.isNormalMap) {
//         glActiveTexture(GL_TEXTURE1);
//         glUniform1i(glGetUniformLocation(m_graphicPiplines[0], "normalMap"), 1);
//         glBindTexture(GL_TEXTURE_2D, m_texturesMap.at(gobject.normalMapId));
//     }

//     struct GModel model = m_modelMap.at(gobject.assetId);
//     glBindVertexArray(model.vao);
//     glDrawArrays(GL_TRIANGLES, 0, model.verticesNumber);
// }

// void OGL::drawTexture(const GObject gobject) 
// {

// }

// void OGL::activateFont(const FontId id)
// {
//     if(0 == m_fonts.count(id)) { 
//         std::cout << "RENDERER::ERROR - No font assing to fontId: " << id << std::endl;
//         return; 
//     }
//     m_actvieFont = &m_fonts.at(id);
// }

// void OGL::drawText2D(std::string content, uint32 x, uint32 y, Color color) 
// {
//     if(nullptr == m_actvieFont) {
//         std::cout << "RENDERER::ERROR -> No active font " << std::endl;
//         return;
//     }
//     // Store initial x for the multiline text support
//     uint32 xInit = x;
    
//     glDisable(GL_DEPTH_TEST);
//     uint16 program = m_graphicPiplines[SYSTEM_GRAPHIC_PIPLINES::TEXT2D];
//     glUseProgram(program);
//     // Update uniforms
//     glUniformMatrix4fv(glGetUniformLocation(program, "ortho"), 1, GL_FALSE, glm::value_ptr(m_orthographic));
//     glUniform4fv(glGetUniformLocation(program, "color"), 1, glm::value_ptr(color.glmVec()));
    
//     glActiveTexture(GL_TEXTURE0);
//     glUniform1i(glGetUniformLocation(program, "character"), 0);
    
//     glBindVertexArray(m_intTextModel.vao);
//     glBindBuffer(GL_ARRAY_BUFFER, m_intTextModel.vbo);



//     for(char symbol : content) {
//         if(0 == m_actvieFont->count(symbol)) {
//             std::cout << "RENDERER::ERROR -> Unsuported symbol <" << symbol << "> in active font " << std::endl;
//             continue;
//         }

//         const Character& c = m_actvieFont->at(symbol);
//         float xpos = x + c.bearing.x;
//         float ypos = y - (c.size.y - c.bearing.y);

//         if(symbol == '\n') {
//             // Proceed with 135% size, it looks good now 
//             // TODO! consider creating some more smart way
//             y -= c.size.y * 1.35;
//             x = xInit;
//             continue;
//         }
 
//         float vertices[6][4] = {
//             xpos           , ypos + c.size.y, 0.0f, 0.0f,
//             xpos + c.size.x, ypos           , 1.0f, 1.0f,
//             xpos           , ypos           , 0.0f, 1.0f,
//             xpos           , ypos + c.size.y, 0.0f, 0.0f,
//             xpos + c.size.x, ypos + c.size.y, 1.0f, 0.0f,
//             xpos + c.size.x, ypos           , 1.0f, 1.0f,
//         };

//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//         glBindTexture(GL_TEXTURE_2D, c.textureId);
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//         x += (c.advance >> 6ul);
//     }

//     glEnable(GL_DEPTH_TEST);
//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
//     glUseProgram(0);
// }

// };


