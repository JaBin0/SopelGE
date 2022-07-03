#pragma once
// Own headers
#include <engine/core/types.h>

namespace Sopel {
class Color {
public:
    Color(uint32 color = 0);
    Color(uint8 red, uint8 green, uint8 blue, uint8 alpha);
    Color(uint32 red, uint32 green, uint32 blue, uint32 alpha);
    Color(float red, float green, float blue, float alpha);

    /** Return color value in the form of  */
    glm::vec4 glmVec() const;

private:
    float m_red;
    float m_green;
    float m_blue;
    float m_alpha;
};
};