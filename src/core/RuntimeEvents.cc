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

bool keyState[512] = { 0 },
    keyStateJustDown[512] = { 0 },
    keyStateJustUp[512] = { 0 };
int cursorX, cursorY;
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
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    RuntimeCore::log(NOTICE, ("Runtime++ window resized to (" 
                        + to_string(event.window.data1) + ", " + to_string(event.window.data2) + ")").c_str());
                    break;
                }
                break;
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = true;
                keyStateJustDown[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyStateJustUp[event.key.keysym.sym] = true;
                break;
            case SDL_MOUSEMOTION:
                cursorX = event.motion.x;
                cursorY = event.motion.y;
                break;
        }
    }
    done:;
}

void RuntimeEvents::flush(void) {
    for(int i = 0; i < 512; i++) {
        keyStateJustDown[i] = false;
        keyStateJustUp[i] = false;
    }
}

bool RuntimeEvents::keyIsDown(int key) {
    return keyState[key];
}

bool RuntimeEvents::keyJustPressed(int key) {
    return keyStateJustDown[key];
}

bool RuntimeEvents::keyJustReleased(int key) {
    return keyStateJustUp[key];
}

int RuntimeEvents::getCursorX(void) {
    return cursorX;
}

int RuntimeEvents::getCursorY(void) {
    return cursorY;
}

#endif