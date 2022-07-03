#pragma once
// Own headers
#include <engine/core/types.h>

namespace Sopel {

/**  */
struct Texture {
    /** Texture width */
    int32 width = -1;

    /** Texture height */
    int32 height = -1;

    int32 numChannels = -1;

    /** Container for texture pixels data */
    std::vector<uint8> data = {};
};

/**  */
class Material {
public:
    

};};