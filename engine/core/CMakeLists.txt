cmake_minimum_required(VERSION 3.5)

project(EnginePrj 
    VERSION 0.01
    DESCRIPTION "Sopel game engine"
    LANGUAGES CXX )

add_library(SGEEngine STATIC
    Engine.cpp
    entities/Entity.cpp
    entities/IEntitiesManager.cpp
)

target_compile_features(SGEEngine PUBLIC cxx_std_20)
target_link_libraries(SGEEngine LINK_PUBLIC SGEWindowOGL SGERendererOGL)

target_include_directories(SGEEngine PUBLIC ${ROOT_DIR})
target_include_directories(SGEEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})




