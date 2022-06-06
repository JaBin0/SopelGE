#pragma once
// Own headers
#include <engine/core/types.h>

namespace Sopel {
struct Mesh {
    /**  */
    vvec3f vertices;
    vvec3f normals;
    vvec2f textureCoords; 

    uint32 verticesNumber;
    uint32 vertexSize;
};};