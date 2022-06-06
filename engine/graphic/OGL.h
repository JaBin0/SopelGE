#pragma once
// System headers
#include <unordered_map>
// External headers
#include <glad/glad.h>
#include <glm-0.9.8.0/gtc/type_ptr.hpp>
#include <glm-0.9.8.0/gtc/matrix_transform.hpp>
// Own headers
#include <engine/graphic/graphicTypes.h>
#include <engine/graphic/IRenderer.h>

namespace Sopel {
class OGL : public IRenderer {
public: 
    /** Constructor */
    OGL(GLADloadproc procAddress);
    
    ErrorCodes::value registerModel(AssetId id, const Model& model) override;

    ErrorCodes::value registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) override;

    void startFrame() override;
    void draw() override;
    void draw(const GObject gobject) override;

protected:
    /** Maps of registred graphic piplines associated with the GPId's */
    std::unordered_map<GPId, uint16> m_graphicPiplines;

    std::unordered_map<AssetId, struct GModel> m_modelMap;

    /** Prerspective matrix */
    glm::mat4 m_perspective;

    /** Camera matrix */
    glm::mat4 m_camera;

};};