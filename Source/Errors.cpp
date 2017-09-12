#include "../Headers/Errors.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace Celofan {

    void fatalError(std::string errorString) {
        std::cerr << errorString << std::endl;
        SDL_Quit();
        exit(42);
    }

}
