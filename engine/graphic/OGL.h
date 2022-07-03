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

    ErrorCodes::value registerFont(FontId id, std::string fontFile) override;

    ErrorCodes::value  registerTexture(AssetId id, const Sopel::Texture& texture) override;

    //void drawText2D(FontId id, uint32 x, uint32 y, std::string content) override;

    void activateFont(const FontId id) override;

    void drawText2D(std::string content, uint32 x, uint32 y, Color color) override;

    void startFrame(double time) override;
    void draw() override;
    void draw(const GObject gobject) override;
    void drawTexture(const GObject gobject) override;

protected:
    /** Maps of registred graphic piplines associated with the GPId's */
    std::unordered_map<GPId, uint16> m_graphicPiplines;

    std::unordered_map<AssetId, struct GModel> m_modelMap;

    /** Maps of registred textures associated with the Assets id's */
    std::unordered_map<AssetId, uint32> m_texturesMap;
    

    std::unordered_map<FontId, Font> m_fonts;
    Font* m_actvieFont;

    /** Internal GModel for Text feature */
    GModel m_intTextModel;


    // uint32 m_textVao;
    // uint32 m_textVbo;

    glm::mat4 m_orthographic;
    /** Prerspective matrix */
    glm::mat4 m_perspective;

    /** Camera matrix */
    glm::mat4 m_camera;

};};