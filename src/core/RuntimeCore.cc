#ifndef RUNTIME_SRC_CORE_CORE_CC_
#define RUNTIME_SRC_CORE_CORE_CC_

#include "RuntimeCore.h"
#include "../state/implementation/DebugState.h"

const string RuntimeCore::version = "1.1.6";
bool RuntimeCore::running = false;
unsigned int RuntimeCore::targetFPS = 60.0f;
double RuntimeCore::deltaTime = (1 / (float)targetFPS);

RuntimeUtilities * RuntimeCore::utilities = nullptr;
RuntimeEvents * RuntimeCore::events = nullptr;
RuntimeProcessManager * RuntimeCore::processes = nullptr;
RuntimeWindow * RuntimeCore::window = nullptr;
RuntimeGUI * RuntimeCore::gui = nullptr;
RuntimeRenderer * RuntimeCore::renderer = nullptr;
RuntimeEngineState * RuntimeCore::currentState = nullptr;

RuntimeCore::RuntimeCore(RuntimeEngineState * entryState, int width, int height, char * title) {
    
    if(entryState == nullptr) {
        log(ERROR, "You must invoke Runtime++ with a valid and concrete RuntimeEngineState.");
        exit(-1);
    }
    
    // Init utilities
    RuntimeUtilities utils;
    RuntimeCore::utilities = &utils;

    // Init window and context
    RuntimeWindow win(width, height, title);
    RuntimeCore::window = &win;

    // Init process manager
    RuntimeProcessManager process;
    RuntimeCore::processes = &process;
    
    // Init input
    RuntimeEvents in;
    RuntimeCore::events = &in;

    // Init GUI
    RuntimeGUI g;
    RuntimeCore::gui = &g;

    // Init renderer
    RuntimeRenderer render;
    RuntimeCore::renderer = &render;

    setState(entryState);
    
    // log(NOTICE, "Runtime++ version: " + VERSION);
    log(SUCCESS, "All Runtime++ processes and contexts created successfully!");
    run();
}

RuntimeCore::~RuntimeCore() {}

void RuntimeCore::setState(RuntimeEngineState * state) {
    if(RuntimeCore::currentState != nullptr) 
        RuntimeCore::currentState->end();
    RuntimeCore::currentState = state;
    if(RuntimeCore::currentState != nullptr) {
        RuntimeCore::currentState->begin();
        log(NOTICE, "Runtime++ engine state is now set to \"" + RuntimeCore::currentState->getName() + "\"");
        return;
    }
    log(NOTICE, "Runtime++ engine state is now set to a NULL state. No instruction will be processed.");
}   

// Main engine loop lives in here.
void RuntimeCore::run(void) {
    RuntimeCore::running = true;

    auto now = chrono::high_resolution_clock::now(),
        last = now,
        dtcn = now,
        dtcl = now;
    long long int delta = 0;

    log(NOTICE, "Runtime++ is now running!");
    while(RuntimeCore::running) {
        last = now;
        now = chrono::high_resolution_clock::now();
        delta += chrono::duration_cast<chrono::nanoseconds>((now - last)).count();
        if(delta > (1000000000.0f / targetFPS)) {
            // Clock
            dtcn = chrono::high_resolution_clock::now();
            deltaTime = (chrono::duration_cast<chrono::nanoseconds>((dtcn - dtcl)).count()) / 1000000000.0f;
            dtcl = chrono::high_resolution_clock::now();
            delta = 0;
            RuntimeCore::events->pollEvents();
            if(RuntimeCore::currentState == nullptr) continue;
            RuntimeCore::currentState->instruction();
            RuntimeCore::processes->tick();
            RuntimeCore::renderer->clear();
            RuntimeCore::renderer->draw();
            RuntimeCore::renderer->swapGLBuffers();
            RuntimeCore::events->flush();
        }
    }
}

void RuntimeCore::stop(void) {
    RuntimeCore::running = false;
    if(RuntimeCore::currentState != nullptr) 
        RuntimeCore::currentState->end();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(RuntimeCore::window->getGlContext());
    SDL_DestroyWindow(RuntimeCore::window->getWindow());
    SDL_Quit();
    log(SUCCESS, "All Runtime++ processes and contexts disposed of successfully.");
}

void RuntimeCore::log(LogType type, string message) {
    switch(type) {
        #ifdef __APPLE__
            case SUCCESS: cout << "\x1b[32m[Runtime++ SUCCESS]\x1b[0m "; break;
            case NOTICE: cout << "\x1b[33m[Runtime++ NOTICE]\x1b[0m "; break;
            case ERROR: cout << "\x1b[31m[Runtime++ ERROR]\x1b[0m "; break;
        #elif __linux__
            case SUCCESS: cout << "\033m[32m[Runtime++ SUCCESS]\033[0m "; break;
            case NOTICE: cout << "\033m[33m[Runtime++ NOTICE]\033[0m "; break;
            case ERROR: cout << "\033m[31m[Runtime++ ERROR]\033[0m "; break;
        #elif _WIN32
            case SUCCESS: cout << "\033m[32m[Runtime++ SUCCESS]\033[0m "; break;
            case NOTICE: cout << "\033m[33m[Runtime++ NOTICE]\033[0m "; break;
            case ERROR: cout << "\033m[31m[Runtime++ ERROR]\033[0m "; break;
        #endif
    }
    cout << message << endl;
}

int main(void) {
    DebugState debug;
    RuntimeCore core(&debug, 1280, 720, (char *)"Runtime");
}

#endif
