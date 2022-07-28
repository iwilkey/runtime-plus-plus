#ifndef RUNTIME_SRC_GFX_GUI_H_
#define RUNTIME_SRC_GFX_GUI_H_

#include <iostream>
using namespace std;

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_opengl3.h"

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
        
    private:
        float scale;
};

#endif