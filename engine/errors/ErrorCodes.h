#pragma once

namespace Sopel {
struct ErrorCodes {
    enum value {
        _NO_ERROR = 0,
        READING_ASSET_FILE_FAILED,
        READING_SHADER_FILE_FAILED,
        COMPILING_SHADER_FAILED,
        LINKING_GRAHPICPIPLINE_FAILED
    };
};};