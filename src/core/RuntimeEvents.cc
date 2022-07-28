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
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        RuntimeCore::stop();
                        goto done;
                        break;
                }
                break;
        }
    }
    done:;
}

#endif