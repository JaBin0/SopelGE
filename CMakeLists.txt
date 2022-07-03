cmake_minimum_required(VERSION 3.5)
project(SopelGE
        VERSION 0.0.1
        DESCRIPTION "Engine"
        LANGUAGES CXX C)

add_library(Sopel STATIC 
            engine/externals/glad.c
            engine/core/Engine.cc
            engine/core/Color.cc
            engine/graphic/OGL.cc
            engine/assets/IAssetsManager.cc
            engine/assets/AssimpAssetsManager.cc  
        )

target_compile_features(Sopel PRIVATE cxx_std_20 )

target_link_directories(Sopel PUBLIC
        #${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64/freetype   
        /f/Windows/_env/msys64/mingw64/bin/
        ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64  
        ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs
)

target_link_libraries (Sopel LINK_PUBLIC assimp opengl32 glfw3 freetype)

target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/includes)


#arget_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/FooModule)
