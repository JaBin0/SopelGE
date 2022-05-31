#pragma once
// Own headers
#include <engine/graphic/IRenderer.h>

namespace Sopel {
class OGL : public IRenderer {
public: 
    ErrorCodes::value registerModel(AssetId id, const Model& model) override;

};};