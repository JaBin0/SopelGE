#pragma once
// Own headers
#include <engine/common/BasicTypes.h>

namespace Sopel {
    enum SYSTEM_GRAPHIC_PIPELINES {
        DEFAULT = 0,
        TEXT2D,
        POINT,
        COUNT
    };

/** Structure to hold all necessary information about graphic model */
struct GMesh {
    uint32 vao;
    uint32 vbo;
    uint32 verticesNumber;
};

struct GPipeline {
    uint32 id;
    std::string vertexShaderFile;
    std::string fragmentShaderFile;
};

struct GColor {
    GColor(uint32 color) {
        r = static_cast<float>((color >> 24) & 0xFF) / 255.0f;
        g = static_cast<float>((color >> 16) & 0xFF) / 255.0f;
        b = static_cast<float>((color >> 8)  & 0xFF) / 255.0f;
        a = static_cast<float>((color)       & 0xFF) / 255.0f;
    };
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 0.0f;
};
};


// Struct to store data about single character
// struct Character {
//     uint32 textureId; // ID handle of the glyph texture
//     glm::ivec2 size; // Size of glyph
//     glm::ivec2 bearing; // Offset from baseline to left/top glyph
//     uint32 advance;
// };

// using Font = std::map<char, Character>;