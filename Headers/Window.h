#ifndef CELOFAN_WINDOW_H
#define CELOFAN_WINDOW_H


#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Celofan {

    enum WindowFlasgs {
        INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x3
    };

    class Window {
    public:
        Window();

        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

        void swapBuffer();

        int getScreenWidth() const;

        int getScreenHeight() const;

        void setWindowTitle(const std::string& windowTitle);

    private:
        SDL_Window *_sdlWindow;
        int _screenWidth, _screenHeight;
    };
}

#endif //CELOFAN_WINDOW_H
