#ifndef RUNTIME_SRC_GFX_GUI_H_
#define RUNTIME_SRC_GFX_GUI_H_

#include <iostream>
using namespace std;

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../../runtime-plus-plus-libraries/imgui-sdl-static/imgui.h"
#include "../../runtime-plus-plus-libraries/imgui-sdl-static/imgui_impl_opengl3.h"

#include "../process/RProcess.h"

class RuntimeGUI {

    public:
        RuntimeGUI();
        ~RuntimeGUI();

        void newGUIFrame(void);
        void renderGUI(void);

        void setScale(float);
        float getScale(void);

        // onGUI presets...
        void debugEngineControl(void);
        void debugInputStatus(void);
        void debugConsole(void);
        
    private:
        float scale;
};

#endif
