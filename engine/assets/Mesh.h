#pragma once
// // Own headers
// #include <engine/core/types.h>

// namespace SopelGE {
// struct Mesh {
//     /**  */
//     vvec3f vertices;
//     vvec3f normals;
//     vvec2f textureCoords; 
//     vvec3f tangents;

//     uint32 verticesNumber;
//     uint32 vertexSize;
// };};

#include <engine/common/BasicTypes.h>

namespace Sopel {

class Mesh {
public:
    vecf vertices;
};

};