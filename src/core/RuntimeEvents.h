#ifndef RUNTIME_SRC_CORE_EVENTS_H_
#define RUNTIME_SRC_CORE_EVENTS_H_

#include <iostream>
#include <vector>
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
        bool cursorButtonIsDown(int);
        bool cursorButtonJustPressed(int);
        bool cursorButtonJustReleased(int);
        int getCursorX(void);
        int getCursorY(void);
        float getCursorScrollX(void);
        float getCursorScrollY(void);
        int getCursorChangeInX(void);
        int getCursorChangeInY(void);
        vector<int> currentKeyState(void);
        vector<int> currentCursorState(void);
        bool windowJustResized(void);

    private:
};

#endif
