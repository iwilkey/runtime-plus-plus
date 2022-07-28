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
    private:
};

#endif