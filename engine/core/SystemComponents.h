#pragma once
// External headers
#include <glm-0.9.8.0/gtc/type_ptr.hpp>
#include <glm-0.9.8.0/gtc/matrix_transform.hpp>
// Own headers
#include <engine/core/Component.h>

/** Test component to furter develop render engine */
_COMPONENT(GObject) {
    AssetId assetId;
    glm::mat4 transformation;
};