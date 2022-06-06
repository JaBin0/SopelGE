#pragma once
// System headers
#include <inttypes.h>
#include <vector>
// External headers
#include <glm-0.9.8.0/vec2.hpp>
#include <glm-0.9.8.0/vec3.hpp>


using int8   = int8_t;
using int16  = int16_t;
using int32  = int32_t;
using int64  = int64_t;

using uint8  = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using AssetId = uint32;
#define INVALID_ASSETID 0xFFFFFFFF

using vecf = std::vector<float>;
using vvec3f = std::vector<glm::vec3>;
using vvec2f = std::vector<glm::vec2>;

using GPId = uint16;

