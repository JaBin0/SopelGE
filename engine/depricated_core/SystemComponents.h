#pragma once
// External headers
#include <glm-0.9.8.0/gtc/type_ptr.hpp>
#include <glm-0.9.8.0/gtc/matrix_transform.hpp>
// Own headers
#include <engine/core/Component.h>

/** Test component to furter develop render engine */
_COMPONENT(GObject) {
    AssetId assetId = 0;
    glm::mat4 transformation = glm::mat4(1.0f);
    glm::vec4 color = glm::vec4(1.0f);
    bool isTextured = 0;
    TextureId textureId = 0;
    glm::vec2 textureScale = glm::vec2(1.0f);
    TextureId normalMapId = 0;
    bool isNormalMap = false;
};