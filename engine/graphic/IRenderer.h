#pragma once
// System headers
#include <string>
// Own headers
#include <engine/core/types.h>
#include <engine/core/Color.h>
#include <engine/assets/SpModel.h>
#include <engine/assets/SpMaterial.h>
#include <engine/errors/ErrorCodes.h>
// TO REMOVE !!!!
#include <engine/core/SystemComponents.h>

namespace Sopel {
class IRenderer {
public:
    /** Virtual Destructor */
    virtual ~IRenderer() = default;

    /** Register model within Graphic system */
    virtual ErrorCodes::value registerModel(AssetId id, const Model& model) = 0;

    /** Register graphic pipline within Graphic system and associate it with given GPId */
    virtual ErrorCodes::value registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) = 0;

    /** Register font within Graphic system and associate it with given FontId */
    virtual ErrorCodes::value registerFont(FontId id, std::string fontFile) = 0;

    /** Register texture within Graphic system and associate it with given TextureId */
    virtual ErrorCodes::value registerTexture(AssetId id, const Sopel::Texture& texture) = 0;

    /**  */
    virtual void activateFont(const FontId id) = 0;

    /**  */
    virtual void drawText2D(std::string content, uint32 x, uint32 y, Color color) = 0;

    /** !!!TO REMOVE!!! Temporary function to develop furter functionality */
    virtual void startFrame(double time) = 0;
    virtual void draw() = 0;
    virtual void draw(const GObject gobject) = 0;
    virtual void drawTexture(const GObject gobject) = 0;

};};