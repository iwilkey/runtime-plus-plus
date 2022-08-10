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
    ImGui::Begin("Runtime++ Engine Control", (bool *)true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("%s", "Runtime++ Debug Engine Control");
    ImGui::Text("%s", ("Runtime++ version: " + RuntimeCore::version).c_str());
    ImGui::SliderInt("Runtime++ target FPS", targFPS, 1, 120);
    ImGui::Text("%s", ("Runtime++ current FPS: " + to_string(1.0f / RuntimeCore::deltaTime)).c_str());
    ImGui::Text("%s", ("Runtime++ current SPF (delta time): " + to_string(RuntimeCore::deltaTime)).c_str());
    ImGui::Text("%s", ("Runtime++ current GUI scale: " + to_string(RuntimeCore::gui->getScale())).c_str());

    // An example of using Runtime++ processes...
    if(RuntimeCore::events->windowJustResized()) 
        RuntimeCore::processes->addProcess("show-window", 3.0f);
    if(RuntimeCore::processes->isActive("show-window")) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 0, 255)));
        ImGui::Text("%s", "Runtime++ window just resized.");
        ImGui::PopStyleColor(1);
    }

    ImGui::Text("%s", ("Runtime++ window dimensions (width, height): " + to_string(RuntimeCore::window->getWidth()) 
        + ", " + to_string(RuntimeCore::window->getHeight())).c_str());
    ImGui::Text("%s", ("Runtime++ window aspect ratio: " + to_string(RuntimeCore::window->getAspectRatio())).c_str());
    ImGui::End();
}

void RuntimeGUI::debugInputStatus(void) {
    ImGui::Begin("Runtime++ Input Status", (bool *)true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("%s", "Runtime++ Debug Input Status");

    // Active keys
    ImGui::Text("%s", "Active keys list");
    vector<int> activeKeys = RuntimeCore::events->currentKeyState();
    if(activeKeys.size() == 0) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
        ImGui::Text("%s", " NO KEYS ACTIVE.");
        ImGui::PopStyleColor(1);
    } else {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 255, 0)));
        for(int i = 0; i < activeKeys.size(); i++) {
            string s = " ID: ";
            s.push_back((char)activeKeys[i]);
            ImGui::Text("%s", s.c_str());
        }
        ImGui::PopStyleColor(1);
        ImGui::Text("%s", (" Found (" + to_string(activeKeys.size()) + ") active key(s).").c_str());
    }

    // Cursor window coords
    ImGui::Text("%s", ("Cursor window coordinates [UpLeft00] (x, y): " + to_string(RuntimeCore::events->getCursorX()) 
        + ", " + to_string(RuntimeCore::events->getCursorY())).c_str());
    
    // Cursor delta
    ImGui::Text("%s", ("Cursor delta (dx, dy): " + to_string(RuntimeCore::events->getCursorChangeInX()) 
        + ", " + to_string(RuntimeCore::events->getCursorChangeInY())).c_str());

    // Cursor scroll
    ImGui::Text("%s", ("Cursor scroll (x, y): " + to_string(RuntimeCore::events->getCursorScrollX()) 
        + ", " + to_string(RuntimeCore::events->getCursorScrollY())).c_str());

    // Active cursors
    ImGui::Text("%s", "Active cursor button list");
    vector<int> activeCursors = RuntimeCore::events->currentCursorState();
    if(activeCursors.size() == 0) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
        ImGui::Text("%s", " NO CURSOR BUTTONS ACTIVE.");
        ImGui::PopStyleColor(1);
    } else {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 255, 0)));
        for(int i = 0; i < activeCursors.size(); i++) {
            string s = " ID: " + to_string(activeCursors[i]);
            ImGui::Text("%s", s.c_str());
        }
        ImGui::PopStyleColor(1);
        ImGui::Text("%s", (" Found (" + to_string(activeCursors.size()) + ") active cursor button(s).").c_str());
    }

    ImGui::End();
}

void RuntimeGUI::debugConsole(void) {
    ImGui::Begin("Runtime++ Console", (bool *)true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::End();
}

#endif
