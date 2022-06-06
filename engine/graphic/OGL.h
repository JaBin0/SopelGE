#pragma once
// System headers
#include <unordered_map>
// External headers
#include <glad/glad.h>
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

    void draw() override;

protected:
    /** Maps of registred graphic piplines associated with the GPId's */
    std::unordered_map<GPId, uint16> m_graphicPiplines;

    std::unordered_map<AssetId, struct GModel> m_modelMap;
};};