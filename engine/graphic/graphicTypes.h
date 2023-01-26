#pragma once
// Own headers
#include <engine/common/BasicTypes.h>

namespace Sopel {
    enum SYSTEM_GRAPHIC_PIPLINES {
        DEFAULT = 0,
        TEXT2D,
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

};

// Struct to store data about single character
// struct Character {
//     uint32 textureId; // ID handle of the glyph texture
//     glm::ivec2 size; // Size of glyph
//     glm::ivec2 bearing; // Offset from baseline to left/top glyph
//     uint32 advance;
// };

// using Font = std::map<char, Character>;