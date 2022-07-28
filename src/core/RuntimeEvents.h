#ifndef RUNTIME_SRC_CORE_EVENTS_H_
#define RUNTIME_SRC_CORE_EVENTS_H_

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_sdl.h"

class RuntimeEvents {
    public:
        RuntimeEvents();
        ~RuntimeEvents();

        void pollEvents(void);
        void flush(void);
        
        bool keyIsDown(int);
        bool keyJustPressed(int);
        bool keyJustReleased(int);
        int getCursorX(void);
        int getCursorY(void);

    private:
};

#endif