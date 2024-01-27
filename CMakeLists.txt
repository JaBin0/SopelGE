cmake_minimum_required(VERSION 3.5)

project(SopelGE
        VERSION 0.0.1
        DESCRIPTION "Sopel game engine"
        LANGUAGES CXX C)

# add_library(Sopel STATIC 
#         #     engine/core/ECSGameEngine.cc
#         #     engine/assets/IAssetsManager.cc
#         #     engine/assets/AssimpAssetsManager.cc  
#         #     engine/externals/glad.c
#         #     engine/core/Engine.cc
#         #     engine/core/Color.cc
#         #     engine/graphic/OGL.cc
#         )

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(engine/assets)
add_subdirectory(engine/graphic)
add_subdirectory(engine/window)
add_subdirectory(engine/core)
add_subdirectory(engine/config)
add_subdirectory(tools/level_editor)




# target_compile_features(Sopel PRIVATE cxx_std_20 )

# target_link_directories(Sopel PUBLIC
#         #${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64/freetype   
#         /f/Windows/_env/msys64/mingw64/bin/
#         # ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64  
#         # ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs
# )

# target_link_libraries (Sopel LINK_PUBLIC assimp)
# # opengl32 glfw3 freetype
# target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/includes)




#arget_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/FooModule)

# add_library(Sopel STATIC 
#         engine/core/ECSGameEngine.cc
#         engine/assets/IAssetsManager.cc
#         engine/assets/AssimpAssetsManager.cc  
#         #     engine/externals/glad.c
#         #     engine/core/Engine.cc
#         #     engine/core/Color.cc
#         #     engine/graphic/OGL.cc
#         )