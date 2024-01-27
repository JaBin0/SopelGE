cmake_minimum_required(VERSION 3.5)
project(SGESettingsProject
        VERSION 0.01
        DESCRIPTION "Sopel approach towords setting rquriement"
        LANGUAGES CXX)

# ======================== ======================== ======================== ========================
add_library(SGESettings STATIC
        Settings.cpp
)

target_compile_features(SGESettings PUBLIC cxx_std_20)

target_include_directories(SGESettings PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ROOT_DIR}/engine
)
