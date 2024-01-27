cmake_minimum_required(VERSION 3.5)
project(SGEWindowPrj
        VERSION 0.0.1
        DESCRIPTION "Window with context for graphic interface"
        LANGUAGES CXX)

# ======================== ======================== ======================== ========================
add_library(SGEWindowOGL STATIC
        WindowOGL.cpp
)

target_compile_features(SGEWindowOGL PUBLIC cxx_std_20)
find_package(OpenGL REQUIRED)
# GLFW

target_include_directories(SGEWindowOGL PUBLIC ${ROOT_DIR}/../Externals/glfw/3.3.8/include)
target_include_directories(SGEWindowOGL PUBLIC ${ROOT_DIR}/../Externals/glm/0.9.8.0/include)
target_include_directories(SGEWindowOGL PUBLIC ${ROOT_DIR}/engine)
target_link_directories(SGEWindowOGL PUBLIC
        /f/Windows/_env/msys64/mingw64/bin/
        ${ROOT_DIR}/../Externals/glfw/3.3.8/x64                
)
target_link_libraries(SGEWindowOGL LINK_PUBLIC opengl32 glfw3)

target_include_directories(SGEWindowOGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ======================== ======================== ======================== ========================
add_library(SGEWindow STATIC
        Window.cpp
)

target_compile_features(SGEWindow PUBLIC cxx_std_20)

target_link_libraries(SGEWindow LINK_PUBLIC glfw3)

target_include_directories(SGEWindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(SGEWindow PUBLIC ${ROOT_DIR}/../Externals/glfw/3.3.8/include)

target_link_directories(SGEWindow PUBLIC
        ${ROOT_DIR}/../Externals/glfw/3.3.8/x64                
)




#target_compile_features(Sopel PRIVATE cxx_std_20 )
#add_library(Sopel STATIC 
#        engine/core/ECSGameEngine.cc
#        engine/assets/IAssetsManager.cc                        
#        engine/assets/AssimpAssetsManager.cc  
#        #     engine/externals/glad.c
#        #     engine/core/Engine.cc
#        #     engine/core/Color.cc
#        #     engine/graphic/OGL.cc
#        )

#project(WalterMelonApp
#        VERSION 0.0.1
#        DESCRIPTION "Game"
#        LANGUAGES CXX)
#
#add_executable(WalterMelon 
#               src/WalterMelon.cc)
#
#add_subdirectory(SopelGE)
#
#target_compile_features(WalterMelon PRIVATE cxx_std_20)
#
#target_link_libraries (WalterMelon LINK_PUBLIC Sopel)
#
#target_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SopelGE)
#arget_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/FooModule)



#cmake_minimum_required(VERSION 3.5)
#project(SopelGE
#        VERSION 0.0.1
#        DESCRIPTION "Sopel game engine"
#        LANGUAGES CXX C)
#
#add_library(Sopel STATIC 
#        engine/core/ECSGameEngine.cc
#        engine/assets/IAssetsManager.cc
#        engine/assets/AssimpAssetsManager.cc  
#        #     engine/externals/glad.c
#        #     engine/core/Engine.cc
#        #     engine/core/Color.cc
#        #     engine/graphic/OGL.cc
#        )
#
#
#
#target_link_directories(Sopel PUBLIC
#        #${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64/freetype   
#        /f/Windows/_env/msys64/mingw64/bin/
#        # ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs/x64  
#        # ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/libs
#)
#
#target_link_libraries (Sopel LINK_PUBLIC assimp)
## opengl32 glfw3 freetype
#target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(Sopel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Externals/includes)
#
#
##arget_include_directories(WalterMelon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/FooModule)