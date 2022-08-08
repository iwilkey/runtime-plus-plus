#ifndef RUNTIME_SRC_GFX_RENDERER_CC_
#define RUNTIME_SRC_GFX_RENDERER_CC_

#include "RuntimeRenderer.h"
#include "../core/RuntimeCore.h"

RuntimeRenderer::RuntimeRenderer() {
    setClearColorRGB255(35.0f, 35.0f, 35.0f);
    RuntimeCore::log(SUCCESS, "RuntimeRenderer object construction complete!");
}

RuntimeRenderer::~RuntimeRenderer() {
    RuntimeCore::log(SUCCESS, "RuntimeRenderer object destruction complete!");
}

void RuntimeRenderer::setClearColorRGB1(float r, float g, float b) {
    if(r > 1.0f || g > 1.0f || b > 1.0f) {
        RuntimeCore::log(ERROR, "You cannot pass RuntimeRenderer::setClearColorRGB1() any values greater than 1.0!");
        return;
    } else if(r < 0.0f || g < 0.0f || b < 0.0f) {
        RuntimeCore::log(ERROR, "You cannot pass RuntimeRenderer::setClearColorRGB1() any values less than 0.0!");
        return;
    }
    glClearColor(r, g, b, 1.0f);
    RuntimeCore::log(SUCCESS, "glClearColor set.");
}

void RuntimeRenderer::setClearColorRGB255(float r, float g, float b) {
    if(r > 255.0f || g > 255.0f || b > 255.0f) {
        RuntimeCore::log(ERROR, "You cannot pass RuntimeRenderer::setClearColorRGB255() any values greater than 255.0!");
        return;
    } else if(r < 0.0f || g < 0.0f || b < 0.0f) {
        RuntimeCore::log(ERROR, "You cannot pass RuntimeRenderer::setClearColorRGB255() any values less than 0.0!");
        return;
    }
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    RuntimeCore::log(SUCCESS, "glClearColor set.");
}

void RuntimeRenderer::clear(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RuntimeRenderer::draw(void) {
    // Draw game stuff...

    // Render contexts will go here.
    RuntimeCore::currentState->renderContext();
    
    // Draw GUI...
    RuntimeCore::gui->newGUIFrame();
    RuntimeCore::currentState->onGUI();
    RuntimeCore::gui->renderGUI();
}

void RuntimeRenderer::swapGLBuffers(void) {
    SDL_GL_SwapWindow(RuntimeCore::window->getWindow());
}

#endif
