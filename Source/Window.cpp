#include <cstdio>

#include "../Headers/Errors.h"
#include "../Headers/Window.h"

namespace Celofan {

    Window::Window() {

    }

    Window::~Window() {

    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

        Uint32 flags = SDL_WINDOW_OPENGL;

        if (currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }
        if (currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }

        //Create the SDL window and check for errors
        _sdlWindow = SDL_CreateWindow(windowName.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,
                                      screenHeight, flags);

        if (_sdlWindow == nullptr) {
            fatalError("Error opening the SDL window");
        }

        // Create the OpenGL context and check for errors
        SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

        if (glContext == nullptr) {
            fatalError("Error creating the SDL_GL context");
        }

        // Initialize GLEW and check for errors
        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            fatalError("Could not initilaize glew");
        }

        // Check OpenGL Version
        printf("*** OpenGL Version %s ***\n", glGetString(GL_VERSION));

        //Set background color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        // Set VSYNC off
        SDL_GL_SetSwapInterval(0);

        //Enable alpha blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(_sdlWindow);
    }

    int Window::getScreenWidth() const {
        return _screenWidth;
    }

    int Window::getScreenHeight() const {
        return _screenHeight;
    }

    void Window::setWindowTitle(const std::string &windowTitle) {
        SDL_SetWindowTitle(_sdlWindow, windowTitle.data());
    }

}
