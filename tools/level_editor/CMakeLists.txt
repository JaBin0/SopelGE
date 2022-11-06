cmake_minimum_required(VERSION 3.5)
project(SGELevelEditorApp
        VERSION 0.0.1
        DESCRIPTION "Level editor based on the Sopel GameEngine"
        LANGUAGES CXX)

add_executable(SGELevelEditor
        src/SGELevelEditor.cpp
)

target_compile_features(SGELevelEditor PRIVATE cxx_std_20)
target_link_libraries(SGELevelEditor LINK_PUBLIC SGEWindowOGL SGERendererOGL)      

target_include_directories(SGELevelEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#target_include_directories(SGELevelEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../engine/window)
#target_include_directories(SGELevelEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../engine/graphic)










# #target_include_directories(SGELevelEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../engine/window)
# 


