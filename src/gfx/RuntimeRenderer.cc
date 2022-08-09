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
    // Render contexts will go here.
    RuntimeCore::currentState->glRender();
    // Draw GUI...
    RuntimeCore::gui->newGUIFrame();
    RuntimeCore::currentState->guiRender();
    RuntimeCore::gui->renderGUI();
}

void RuntimeRenderer::swapGLBuffers(void) {
    SDL_GL_SwapWindow(RuntimeCore::window->getWindow());
}

GLuint RuntimeRenderer::addShaderSource(string name, GLenum type, const char * source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        RuntimeCore::log(ERROR, "Runtime++ encountered a fatal error while trying to compile a shader! Please see more information below...");
        cout << buffer << endl;
        RuntimeCore::stop();
    }
    this->shaders.push_back(make_pair(name, shader));
    return shader;
}

GLuint RuntimeRenderer::getShader(string name) {
    for(pair<string, GLuint> entry : shaders)
        if(entry.first == name)
            return entry.second;
    RuntimeCore::log(ERROR, "Runtime++ is trying to return a shader that does not exist.");
    return 0;
}

#endif
