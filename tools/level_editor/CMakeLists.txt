cmake_minimum_required(VERSION 3.5)
project(SGELevelEditorApp
        VERSION 0.0.1
        DESCRIPTION "Level editor based on the Sopel GameEngine"
        LANGUAGES CXX)

add_executable(SGELevelEditor
               src/SGELevelEditor.cpp
)

target_compile_features(SGELevelEditor PRIVATE cxx_std_20)

target_include_directories(SGELevelEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
