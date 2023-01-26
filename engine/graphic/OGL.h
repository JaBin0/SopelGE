// #pragma once
// // System headers
// 
// // External headers
// #include <glad/glad.h>
// #include <glm-0.9.8.0/gtc/type_ptr.hpp>
// #include <glm-0.9.8.0/gtc/matrix_transform.hpp>
// // Own headers

#include <unordered_map>

#include <glad/gl.h>

#include "IRenderer.h"
#include <engine/graphic/graphicTypes.h>
#include <engine/assets/Model.h>

namespace Sopel {
class OGL : public IRenderer {
public: 
    /** Constructor */
    OGL() = delete;
    OGL(GLADloadfunc procAddress);
    
//     ErrorCodes::value registerModel(AssetId id, const Model& model) override;

//     ErrorCodes::value registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) override;

//     ErrorCodes::value registerFont(FontId id, std::string fontFile) override;

//     ErrorCodes::value  registerTexture(AssetId id, const Sopel::Texture& texture) override;

//     //void drawText2D(FontId id, uint32 x, uint32 y, std::string content) override;

//     void activateFont(const FontId id) override;

//     void drawText2D(std::string content, uint32 x, uint32 y, Color color) override;

    void startFrame(double time) override;

    bool registerMesh(const AssetID assetId, const Mesh& mesh) override;

    bool registerGraphicPipeline(GPID id, std::string vertexShaderFile, std::string fragmentShaderFile) override;

    void setTime(const float time) override;

    void draw(const GPID gpid, const AssetID assetId, const glm::mat4 transform) override;

//     void draw() override;
//     void draw(const GObject gobject) override;
//     void drawTexture(const GObject gobject) override;

protected:
    /**! \brief Mapping from AssetID to it representation within Renderer */
    std::unordered_map<AssetID, GMesh> _meshes;

    /**! \brief */
    std::unordered_map<GPID, GPipeline> _pipelines;

    /**! \brief */
    glm::mat4 _perspective;

    /**! \brief */
    glm::mat4 _camera;

    /**! \brief Time of the current frame */
    float _time;

    /**! \brief */
    uint32 _cgp;

//     /** Maps of registred graphic piplines associated with the GPId's */
//     std::unordered_map<GPId, uint16> m_graphicPiplines;

//     std::unordered_map<AssetId, struct GModel> m_modelMap;

//     /** Maps of registred textures associated with the Assets id's */
//     std::unordered_map<AssetId, uint32> m_texturesMap;
    

//     std::unordered_map<FontId, Font> m_fonts;
//     Font* m_actvieFont;

//     /** Internal GModel for Text feature */
//     GModel m_intTextModel;


//     // uint32 m_textVao;
//     // uint32 m_textVbo;

//     glm::mat4 m_orthographic;


};};