#ifndef RUNTIME_SRC_WINDOW_H_
#define RUNTIME_SRC_WINDOW_H_

#include <iostream>
using namespace std;

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_sdl.h"
#include "../../lib/imgui/imgui_impl_opengl3.h"

class RuntimeWindow {
    public:

        RuntimeWindow(int, int, char *);
        ~RuntimeWindow();

        SDL_Window * getWindow(void);
        SDL_GLContext getGlContext(void);
        int getWidth(void);
        int getHeight(void);
        char * getTitle(void);

    private:
        int width, height;
        char * title;
        SDL_Window * window;
        SDL_GLContext glContext;
};

#endif