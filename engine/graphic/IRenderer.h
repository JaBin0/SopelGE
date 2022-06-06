#pragma once
// System headers
#include <string>
// Own headers
#include <engine/core/types.h>
#include <engine/assets/Model.h>
#include <engine/errors/ErrorCodes.h>

namespace Sopel {
class IRenderer {
public:
    /** Virtual Destructor */
    virtual ~IRenderer() = default;

    /** Register model within Graphic system */
    virtual ErrorCodes::value registerModel(AssetId id, const Model& model) = 0;

    /** Register graphic pipline within Graphic system and associate it with given GPId */
    virtual ErrorCodes::value registerGraphicPipline(GPId id, std::string vertexShaderSrcFile, std::string fragmentShaderSrcFile) = 0;

    /** !!!TO REMOVE!!! Temporary function to develop furter functionality */
    virtual void draw() = 0;
};};