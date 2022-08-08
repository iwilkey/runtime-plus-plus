#ifndef RUNTIME_SRC_CORE_EVENTS_CC_
#define RUNTIME_SRC_CORE_EVENTS_CC_

#include "RuntimeEvents.h"
#include "RuntimeCore.h"

RuntimeEvents::RuntimeEvents() {
    RuntimeCore::log(SUCCESS, "RuntimeInput object construction complete!");
}

RuntimeEvents::~RuntimeEvents() {
    RuntimeCore::log(SUCCESS, "RuntimeInput object destruction complete!");
}

// Local data keep for input.
vector<int> keyState, keyStateJustDown, keyStateJustUp,
    cursorState, cursorStateJustDown, cursorStateJustUp;
int cursorX, cursorY, cursordX, cursordY;
float cursorScrollX, cursorScrollY;
bool cursorMotionThisFrame = false,
    cursorScrollThisFrame = false,
    windowResizeThisFrame = false;

void RuntimeEvents::pollEvents(void) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                RuntimeCore::stop();
                goto done;
                break;
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        RuntimeCore::window->setWidth(event.window.data1);
                        RuntimeCore::window->setHeight(event.window.data2);
                        RuntimeCore::log(NOTICE, ("Runtime++ window resized to (" 
                            + to_string(event.window.data1) + ", " + to_string(event.window.data2) + ")").c_str());
                        windowResizeThisFrame = true;
                        break;
                }
                break;
            case SDL_KEYDOWN:
                if(RuntimeCore::utilities->vectorContains(keyState, event.key.keysym.sym) == -1)
                    keyState.push_back(event.key.keysym.sym);
                keyStateJustDown.push_back(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                // TODO: Make utilities library to do common practices.
                RuntimeCore::utilities->vectorErase(keyState, event.key.keysym.sym);
                keyStateJustUp.push_back(event.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                cursordX = event.motion.x - cursorX;
                cursordY = event.motion.y - cursorY;
                cursorX = event.motion.x;
                cursorY = event.motion.y;
                cursorMotionThisFrame = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(RuntimeCore::utilities->vectorContains(cursorState, (int)event.button.button) == -1)
                    cursorState.push_back(event.button.button);
                cursorStateJustDown.push_back(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                RuntimeCore::utilities->vectorErase(cursorState, (int)event.button.button);
                cursorStateJustUp.push_back(event.button.button);
                break;
            case SDL_MOUSEWHEEL:
                cursorScrollX = event.wheel.preciseX;
                cursorScrollY = event.wheel.preciseY;
                cursorScrollThisFrame = true;
                break;
        }
    }
    done:;
}

void RuntimeEvents::flush(void) {
    keyStateJustDown.clear();
    keyStateJustUp.clear();
    cursorStateJustDown.clear();
    cursorStateJustUp.clear();
    if(!cursorMotionThisFrame) {
      cursordX = 0;
      cursordY = 0;   
    } else cursorMotionThisFrame = false;
    if(!cursorScrollThisFrame) {
        cursorScrollX = 0;
        cursorScrollY = 0;
    } else cursorScrollThisFrame = false;
    if(windowResizeThisFrame) windowResizeThisFrame = false;
}

bool RuntimeEvents::keyIsDown(int key) {
    long long int in = RuntimeCore::utilities->vectorContains(keyState, key);
    if(in == -1) return false;
    return true;
}

bool RuntimeEvents::keyJustPressed(int key) {
    long long int in = RuntimeCore::utilities->vectorContains(keyStateJustDown, key);
    if(in == -1) return false;
    return true;
}

bool RuntimeEvents::keyJustReleased(int key) {
    long long int in = RuntimeCore::utilities->vectorContains(keyStateJustUp, key);
    if(in == -1) return false;
    return true;
}

int RuntimeEvents::getCursorX(void) {
    return cursorX;
}

int RuntimeEvents::getCursorY(void) {
    return cursorY;
}

int RuntimeEvents::getCursorChangeInX(void) {
    return cursordX;
}

int RuntimeEvents::getCursorChangeInY(void) {
    return cursordY;
}

float RuntimeEvents::getCursorScrollX(void) {
    return cursorScrollX;
}

float RuntimeEvents::getCursorScrollY(void) {
    return cursorScrollY;
}

bool RuntimeEvents::cursorButtonIsDown(int button) {
    long long int in = RuntimeCore::utilities->vectorContains(cursorState, button);
    if(in == -1) return false;
    return true;
}

bool RuntimeEvents::cursorButtonJustPressed(int button) {
    long long int in = RuntimeCore::utilities->vectorContains(cursorStateJustDown, button);
    if(in == -1) return false;
    return true;
}

bool RuntimeEvents::cursorButtonJustReleased(int button) {
    long long int in = RuntimeCore::utilities->vectorContains(cursorStateJustUp, button);
    if(in == -1) return false;
    return true;
}

vector<int> RuntimeEvents::currentKeyState(void) {
    return keyState;
}

vector<int> RuntimeEvents::currentCursorState(void) {
    return cursorState;
}

bool RuntimeEvents::windowJustResized(void) {
    return windowResizeThisFrame;
}

#endif
