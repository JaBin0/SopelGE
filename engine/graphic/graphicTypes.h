#pragma once

namespace Sopel {
    enum SYSTEM_GRAPHIC_PIPLINES {
        DEFAULT = 0,
        COUNT
    };
};

/** Structure to hold all necessery information about graphic model */
struct GModel {
    uint32 vao;
    uint32 vbo;
    uint32 verticesNumber;
};