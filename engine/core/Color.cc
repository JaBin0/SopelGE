// Own headers
#include <engine/core/Color.h>
// External headers
#include <glm-0.9.8.0/gtc/type_ptr.hpp>
#include <glm-0.9.8.0/gtc/matrix_transform.hpp>

namespace Sopel {
Color::Color(uint32 color)
{
    m_red   = static_cast<float>( color >> 24) / 255.0f;
    m_green = static_cast<float>((color & 0xFF0000) >> 16) / 255.0f;
    m_blue  = static_cast<float>((color & 0xFF00) >> 8) / 255.0f;
    m_alpha = static_cast<float>( color & 0xFF) / 255.0f;
}

Color::Color(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
    m_red   = static_cast<float>(red)   / 255.0f;
    m_green = static_cast<float>(green) / 255.0f;
    m_blue  = static_cast<float>(blue)  / 255.0f;
    m_alpha = static_cast<float>(alpha) / 255.0f;
}

Color::Color(uint32 red, uint32 green, uint32 blue, uint32 alpha)
{
    m_red   = static_cast<float>(red   & 0xFF) / 255.0f;
    m_green = static_cast<float>(green & 0xFF) / 255.0f;
    m_blue  = static_cast<float>(blue  & 0xFF) / 255.0f;
    m_alpha = static_cast<float>(alpha & 0xFF) / 255.0f;
}

Color::Color(float red, float green, float blue, float alpha)
{
    m_red = (red <= 1.0f)? (red >= 0.0f) ? red : 0.0f : 1.0f;
    m_green = (green <= 1.0f)? (green >= 0.0f) ? green : 0.0f : 1.0f;  
    m_blue = (blue <= 1.0f)? (blue >= 0.0f) ? blue : 0.0f : 1.0f;  
    m_alpha = (alpha <= 1.0f)? (alpha >= 0.0f) ? alpha : 0.0f : 1.0f;  
}


glm::vec4 Color::glmVec() const
{
    return glm::vec4(m_red, m_green, m_blue, m_alpha);
}

};