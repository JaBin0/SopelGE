#pragma once
#include <engine/common/BasicTypes.h>

#include <string>

namespace Sopel {

struct Image {
    AssetID id;
    uint32 width;
    uint32 height;
    std::string path;
    uint16 nrChannels;
    std::vector<unsigned char> data;
};
};