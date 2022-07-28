#ifndef RUNTIME_SRC_GFX_GUI_CC_
#define RUNTIME_SRC_GFX_GUI_CC_

#include "RuntimeGUI.h"
#include "../core/RuntimeCore.h"

RuntimeGUI::RuntimeGUI() {
    RuntimeCore::log(SUCCESS, "RuntimeGUI object construction complete!");
}

RuntimeGUI::~RuntimeGUI() {
    RuntimeCore::log(SUCCESS, "RuntimeGUI object construction complete!");
}

void RuntimeGUI::setScale(float scale) {
    if(scale <= 0.0f) {
        RuntimeCore::log(ERROR, "You cannot make the GUI scale less than or equal to zero!");
        return;
    }
    this->scale = scale;
    ImGui::GetIO().FontGlobalScale = scale;
}

float RuntimeGUI::getScale(void) {
    return this->scale;
}

void RuntimeGUI::newGUIFrame(void) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(RuntimeCore::window->getWindow());
    ImGui::NewFrame();
}

void RuntimeGUI::renderGUI(void) {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Debug tools implementation...
int targFPS[] = { 60 };
float guiScale[] = { 1.0f };
void RuntimeGUI::debugEngineControl(void) {
    if(targFPS[0] != RuntimeCore::targetFPS)
          RuntimeCore::targetFPS = targFPS[0];
    if(guiScale[0] != RuntimeCore::gui->getScale())
        RuntimeCore::gui->setScale(guiScale[0]);
    ImGui::Begin("Runtime++ Debug Engine Control", (bool *)true, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%s", ("Runtime++ version: " + RuntimeCore::version).c_str());
    ImGui::SliderInt("Runtime++ target FPS", targFPS, 1, 120);
    ImGui::Text("%s", ("Runtime++ current FPS: " + to_string(1.0f / RuntimeCore::deltaTime)).c_str());
    ImGui::Text("%s", ("Runtime++ current SPF (delta time): " + to_string(RuntimeCore::deltaTime)).c_str());
    ImGui::SliderFloat("Runtime++ GUI scale", guiScale, 0.25f, 10);
    ImGui::End();
}

#endif