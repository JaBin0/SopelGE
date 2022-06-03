#pragma once
// External headers
#include <glad/glad.h>
// Own headers
#include <engine/graphic/IRenderer.h>

namespace Sopel {
class OGL : public IRenderer {
public: 
    /** Constructor */
    OGL(GLADloadproc procAddress);
    
    ErrorCodes::value registerModel(AssetId id, const Model& model) override;

    void draw() override;

};};