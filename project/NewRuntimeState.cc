#ifndef RUNTIME_PROJECT_NEW_RUNTIME_STATE_CC_
#define RUNTIME_PROJECT_NEW_RUNTIME_STATE_CC_

#include "NewRuntimeState.h"
#include "../src/core/RuntimeCore.h"

// How to include SOIL...
// #include "../../../lib/SOIL/src/SOIL.h"

NewRuntimeState::NewRuntimeState() : RuntimeEngineState("NewRuntimeState") {}

// Simple triangle vertices in OpenGL device coordinates.
float vertices[] = {
    -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // Top-left, Red
     1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // Top-right, Green
     1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right, Blue
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f  // Bottom-left, White
};
 // Draw rectangle with two triangles clockwise from top left (OpenGL convention).
GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
};

GLuint shaderProgram,
     vbo,
     vao,
     ebo;

void NewRuntimeState::onBegin(void) {

     // Create VAO...
     glGenVertexArrays(1, &vao);
     glBindVertexArray(vao);

     // Create VBO, load in vertices to GPU...
     glGenBuffers(1, &vbo); // Generating one buffer.
     glBindBuffer(GL_ARRAY_BUFFER, vbo); // Upload data to GPU.
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glGenBuffers(1, &ebo);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER,
          sizeof(elements), elements, GL_STATIC_DRAW);

     // ### Shaders ###
     // Vertex...
     RuntimeCore::renderer->addShaderSource("simple-vertex", GL_VERTEX_SHADER, R"glsl(
          #version 150 core
          in vec2 position;
          in vec3 color;
          out vec3 Color;
          void main() {
               Color = color;
               gl_Position = vec4(position, 0.0, 1.0);
          }
     )glsl");
     
     // Fragment
     RuntimeCore::renderer->addShaderSource("simple-fragment", GL_FRAGMENT_SHADER, R"glsl(
          #version 150 core
          in vec3 Color;
          out vec4 outColor;
          void main() {
               outColor = vec4(Color, 1.0);
          }
     )glsl");

     shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, RuntimeCore::renderer->getShader("simple-vertex"));
     glAttachShader(shaderProgram, RuntimeCore::renderer->getShader("simple-fragment"));
     glBindFragDataLocation(shaderProgram, 0, "outColor");
     glLinkProgram(shaderProgram);
     glUseProgram(shaderProgram);

     GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
     glEnableVertexAttribArray(posAttrib);
     glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                         5 * sizeof(float), 0);
     GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
     glEnableVertexAttribArray(colAttrib);
     glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                         5 * sizeof(float), (void *)(2 * sizeof(float)));

     RuntimeCore::log(SUCCESS, "Debug state loaded successfully.");
}

void NewRuntimeState::onInstruction(void) {
     if(RuntimeCore::events->keyJustPressed(SDLK_ESCAPE))
          RuntimeCore::stop();
}

void NewRuntimeState::glRender(void) {
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void NewRuntimeState::guiRender(void) {
     RuntimeCore::gui->debugEngineControl();
     RuntimeCore::gui->debugInputStatus();
     RuntimeCore::gui->debugConsole();
}

void NewRuntimeState::onEnd(void) {
     glDeleteProgram(shaderProgram);
     glDeleteShader(RuntimeCore::renderer->getShader("simple-fragment"));
     glDeleteShader(RuntimeCore::renderer->getShader("simple-vertex"));
     glDeleteBuffers(1, &vbo);
     glDeleteVertexArrays(1, &vao);
     glDeleteBuffers(1, &ebo);
     RuntimeCore::log(SUCCESS, "\"Debug\" engine state ended successfully.");
}

#endif
