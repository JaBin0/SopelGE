#pragma once
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
};};