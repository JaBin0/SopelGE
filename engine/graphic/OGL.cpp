// // System headers
// #include <iostream>
// #include <fstream>
// // External
// #include <ft2build.h>
// #include FT_FREETYPE_H 
// #include <glm-0.9.8.0/gtc/type_ptr.hpp>
// #include <glm-0.9.8.0/gtc/matrix_transform.hpp>

// // Own headers
// #include <engine/core/types.h>
// #include <engine/graphic/OGL.h>
#include <iostream>

#include "OGL.h"

namespace Sopel {

OGL::OGL(GLADloadfunc procAddress) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    
    int success = gladLoadGL(procAddress);
    if(!success) {
        std::cout << "ERROR: OpenGL function poiters could not be retrive by GLAD" << std::endl;
        return;        
    }
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void OGL::startFrame(double time) {
    glClear(GL_COLOR_BUFFER_BIT);
}

//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

// ErrorCodes::value OGL::registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) 
// {
//     std::cout << "Loading graphic pipline [" << id << "]: <" << vertexShaderSrcFile.data() <<", " << fragmentShaderSrcFile.data() << "> ... ";
//     std::fstream vtShaderFile, fgShaderFile;
//     vtShaderFile.open(vertexShaderSrcFile, std::ios_base::in);
//     fgShaderFile.open(fragmentShaderSrcFile, std::ios_base::in);
//     if(!vtShaderFile.is_open() || !fgShaderFile.is_open()) {
//         std::cout << "Failed" << std::endl
//                   << "   One of the shader source file could not be opened " << std::endl;
//         return ErrorCodes::READING_SHADER_FILE_FAILED;
//     }
//     // Create Vertex Shader
//     std::string vertexShaderSrcStr;
//     std::getline(vtShaderFile, vertexShaderSrcStr, '\0');
//     const char* vertexShaderSrc = vertexShaderSrcStr.data();

//     uint16 vertexShader = glCreateShader(GL_VERTEX_SHADER); 
//     glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//     glCompileShader(vertexShader);

//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
//     if(!success) {
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         vtShaderFile.close();
//         fgShaderFile.close();
//         glDeleteShader(vertexShader);
//         std::cout << "Failed" << std::endl
//                   << "   VERTEX::Info: " << infoLog << std::endl;
//         return ErrorCodes::COMPILING_SHADER_FAILED; 
//     }

//     // Create Fragment Shader
//     std::string fragmentShaderSrcStr;
//     std::getline(fgShaderFile, fragmentShaderSrcStr, '\0');
//     const char* fragmentShaderSrc = fragmentShaderSrcStr.data();

//     uint16 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
//     glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//     glCompileShader(fragmentShader);

//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); 
//     if(!success) {
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         vtShaderFile.close();
//         fgShaderFile.close();
//         glDeleteShader(vertexShader);
//         glDeleteShader(fragmentShader);
//         std::cout << "Failed" << std::endl
//                   << "   FRAGMENT::Info: " << infoLog << std::endl;
//         return ErrorCodes::COMPILING_SHADER_FAILED; 
//     }

//     // Create Graphic pipline
//     uint32 graphicPipline = glCreateProgram();
//     glAttachShader(graphicPipline, vertexShader);
//     glAttachShader(graphicPipline, fragmentShader);
//     glLinkProgram(graphicPipline);

//     glGetProgramiv(graphicPipline, GL_LINK_STATUS, &success);
//     if(!success) {
//         glGetProgramInfoLog(graphicPipline, 512, NULL, infoLog);
//         vtShaderFile.close();
//         fgShaderFile.close();
//         glDeleteShader(vertexShader);
//         glDeleteShader(fragmentShader);
//         glDeleteProgram(graphicPipline);
//         std::cout << "Failed" << std::endl
//                   << "   PROGRAM::Info: " << infoLog << std::endl;
//         return ErrorCodes::LINKING_GRAHPICPIPLINE_FAILED; 
//     }

//     m_graphicPiplines[id] = graphicPipline;
    
//     std::cout << "Success" << std::endl;
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


