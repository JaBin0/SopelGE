cmake_minimum_required(VERSION 3.5)
project(SGEAssets
        VERSION 0.0.1
        DESCRIPTION "Provide assets manager interface for the SopelGE"
        LANGUAGES CXX)

add_library(SGEAssetsManager STATIC
    IAssetsManager.cpp
)

target_compile_features(SGEAssetsManager PUBLIC cxx_std_20)

target_include_directories(SGEAssetsManager PUBLIC ${ROOT_DIR})
target_include_directories(SGEAssetsManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SGEAssetsManager PUBLIC ${ROOT_DIR}/../Externals/assimp/5.2.5/include)

target_link_directories(SGEAssetsManager PUBLIC
        /f/Windows/_env/msys64/mingw64/bin/
        ${ROOT_DIR}/../Externals/assimp/5.2.5/x64                
)
target_link_libraries(SGEAssetsManager LINK_PUBLIC assimp.dll)


#         add_library(SGERendererOGL STATIC
#         OGL.cpp
#         ../../../Externals/glfw/3.3.8/src/glad_gl.c)

# target_include_directories(SGERendererOGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(SGERendererOGL PUBLIC ${ROOT_DIR}/../Externals/glfw/3.3.8/include)

# set(SGERendererOGL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#cmake_minimum_required(VERSION 3.5)
#project(SGEGraphic
#VERSION 0.0.1
#DESCRIPTION "Provide graphic interface for the SopelGE family"
#LANGUAGES CXX)