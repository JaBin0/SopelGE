#pragma once
// System headers
#include <inttypes.h>
#include <vector>
// #include <map>
// 

// // External headers
// #include <glm-0.9.8.0/vec2.hpp>
#include <glm/vec3.hpp>


using int8   = int8_t;
using int16  = int16_t;
using int32  = int32_t;
using int64  = int64_t;

using uint8  = unsigned char;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using vec3f = std::vector<glm::vec3>;
using vecf = std::vector<float>;

using AssetID = uint16;
#define INVALID_ASSET_ID 0xFFFF

using GPID = uint16;
#define INVALID_GP_ID 0xFFFF

// using AssetId = uint32;
// #define INVALID_ASSETID 0xFFFFFFFF

// using vecf = std::vector<float>;
// using vvec3f = std::vector<glm::vec3>;
// using vvec2f = std::vector<glm::vec2>;

// using GPId = uint16;

// using FontId = uint16;
// #ifndef SYSTEM_FONT 
//     #define SYSTEM_FONT 0xFFFE
// #endif
// #define INVALID_FONT 0xFFFF


//using Color = uint32;
// Order is important most right part will go the the top member
// struct _Color {
//     uint8 alpha;
//     uint8 blue;
//     uint8 green;
//     uint8 red;
// };

// union Color {
//     uint32 u32;
//     struct _Color values;
// };

using TextureId = uint32;
