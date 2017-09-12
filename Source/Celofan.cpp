#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "../Headers/Celofan.h"

namespace Celofan {

    int init() {
        //Initialize SDL
        SDL_Init(SDL_INIT_EVERYTHING);

        // Set the double buffer in OpenGL
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }
}