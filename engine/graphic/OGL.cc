// System headers
#include <iostream>
#include <fstream>
// External 
#include <glm-0.9.8.0/gtc/type_ptr.hpp>
#include <glm-0.9.8.0/gtc/matrix_transform.hpp>
// Own headers
#include <engine/core/types.h>
#include <engine/graphic/OGL.h>

namespace Sopel {

AssetId m_testId;

OGL::OGL(GLADloadproc procAddress)
    : m_graphicPiplines{}
{
    int success = gladLoadGLLoader((GLADloadproc)procAddress);
    if(!success) {
        std::cout << "OpenGL function poiters could not be retrive by GLAD" << std::endl;        
    }
    glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
}

ErrorCodes::value OGL::registerModel(AssetId id, const Model& model)
{
    std::cout << "Register new gModel ... ";
    uint32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    vecf data;
    data.reserve(model.mesh.verticesNumber * model.mesh.vertexSize);
    for(uint32 vIndex = 0; vIndex < model.mesh.verticesNumber; ++vIndex) {
        data.push_back(model.mesh.vertices.at(vIndex).x);
        data.push_back(model.mesh.vertices.at(vIndex).y); 
        data.push_back(model.mesh.vertices.at(vIndex).z);  

        data.push_back(model.mesh.textureCoords.at(vIndex).x);
        data.push_back(model.mesh.textureCoords.at(vIndex).y); 

        data.push_back(model.mesh.normals.at(vIndex).x);
        data.push_back(model.mesh.normals.at(vIndex).y); 
        data.push_back(model.mesh.normals.at(vIndex).z);  
    }

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, model.mesh.vertexSize * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_modelMap.insert({id, {vao, vbo, model.mesh.verticesNumber}});
    m_testId = id;
     std::cout << "Success testId: " << m_testId << std::endl;
    return ErrorCodes::_NO_ERROR;
}

ErrorCodes::value OGL::registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) 
{
    std::cout << "Loading graphic pipline [" << id << "]: <" << vertexShaderSrcFile.data() <<", " << fragmentShaderSrcFile.data() << "> ... ";
    std::fstream vtShaderFile, fgShaderFile;
    vtShaderFile.open(vertexShaderSrcFile, std::ios_base::in);
    fgShaderFile.open(fragmentShaderSrcFile, std::ios_base::in);
    if(!vtShaderFile.is_open() || !fgShaderFile.is_open()) {
        std::cout << "Failed" << std::endl
                  << "   One of the shader source file could not be opened " << std::endl;
        return ErrorCodes::READING_SHADER_FILE_FAILED;
    }
    // Create Vertex Shader
    std::string vertexShaderSrcStr;
    std::getline(vtShaderFile, vertexShaderSrcStr, '\0');
    const char* vertexShaderSrc = vertexShaderSrcStr.data();

    uint16 vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        vtShaderFile.close();
        fgShaderFile.close();
        glDeleteShader(vertexShader);
        std::cout << "Failed" << std::endl
                  << "   Info: " << infoLog << std::endl;
        return ErrorCodes::COMPILING_SHADER_FAILED; 
    }

    // Create Fragment Shader
    std::string fragmentShaderSrcStr;
    std::getline(fgShaderFile, fragmentShaderSrcStr, '\0');
    const char* fragmentShaderSrc = fragmentShaderSrcStr.data();

    uint16 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); 
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        vtShaderFile.close();
        fgShaderFile.close();
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        std::cout << "Failed" << std::endl
                  << "   Info: " << infoLog << std::endl;
        return ErrorCodes::COMPILING_SHADER_FAILED; 
    }

    // Create Graphic pipline
    uint32 graphicPipline = glCreateProgram();
    glAttachShader(graphicPipline, vertexShader);
    glAttachShader(graphicPipline, fragmentShader);
    glLinkProgram(graphicPipline);

    glGetProgramiv(graphicPipline, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(graphicPipline, 512, NULL, infoLog);
        vtShaderFile.close();
        fgShaderFile.close();
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(graphicPipline);
        std::cout << "Failed" << std::endl
                  << "   Info: " << infoLog << std::endl;
        return ErrorCodes::LINKING_GRAHPICPIPLINE_FAILED; 
    }

    m_graphicPiplines[id] = graphicPipline;
    
    std::cout << "Success" << std::endl;
    return ErrorCodes::_NO_ERROR;
}

void OGL::draw() 
{
    glm::mat4 perspective =  glm::perspective(glm::radians(45.0f), 
                static_cast<float>(1280.0f)/static_cast<float>(720.0f),
                0.1f, 100.0f);

    glm::mat4 modelMat = glm::mat4(1.0);
    modelMat = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -10.0f));

    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0));

    glClearColor(0.2f, 0.25f, 0.33f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_graphicPiplines[0]);
    glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "projection"), 1, GL_FALSE, glm::value_ptr(perspective));
    glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_graphicPiplines[0], "model"), 1, GL_FALSE, glm::value_ptr(modelMat));

    struct GModel model = m_modelMap.at(m_testId);
    glBindVertexArray(model.vao);

    glDrawArrays(GL_TRIANGLES, 0, model.verticesNumber);
}
};

