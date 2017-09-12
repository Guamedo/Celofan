cmake_minimum_required(VERSION 3.8)
project(Celofan)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DGLEW_STATIC)


set(SOURCE_FILES
        Headers/TextureCache.h
        Source/TextureCache.cpp
        Headers/Errors.h
        Source/Errors.cpp
        Headers/ResourceManager.h
        Source/ResourceManager.cpp
        Headers/IOManager.h
        Source/IOManager.cpp
        Headers/ImageLoader.h
        Source/ImageLoader.cpp
        Headers/GLSLProgram.h
        Source/GLSLProgram.cpp
        Source/Sprite.cpp
        Headers/Sprite.h
        Headers/picoPNG.h
        Source/picoPNG.cpp
        Headers/Vertex.h
        Headers/GLTexture.h
        Source/Celofan.cpp
        Headers/Celofan.h
        Source/Window.cpp
        Headers/Window.h
        Source/Camera2D.cpp
        Headers/Camera2D.h
        Source/SpriteBatch.cpp
        Headers/SpriteBatch.h Source/InputManager.cpp Headers/InputManager.h Headers/Timing.h Source/Timing.cpp)

add_library(Celofan ${SOURCE_FILES})

target_link_libraries(Celofan mingw32 SDL2main SDL2 glew32s opengl32)