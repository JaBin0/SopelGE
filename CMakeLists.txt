cmake_minimum_required(VERSION 3.5)
project(SopelGE
        VERSION 0.0.1
        DESCRIPTION "Engine"
        LANGUAGES CXX)

add_library(Sopel STATIC 
            engine/core/Engine.cc)

target_compile_features(Sopel PRIVATE cxx_std_20 )

target_link_directories(Sopel PUBLIC  
        /f/Windows/_env/msys64/mingw64/bin/  
        ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/lib
)

target_link_libraries (Sopel LINK_PUBLIC assimp)

target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/include)


#arget_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/FooModule)
