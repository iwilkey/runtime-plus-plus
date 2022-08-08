#ifndef RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_CC_
#define RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_CC_

#include "DebugState.h"
#include "../../core/RuntimeCore.h"

DebugState::DebugState() : RuntimeEngineState("Debug") {}

// Simple triangle vertices.
float vertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
};

// Shaders
const char * vertexSource = R"glsl(
     #version 150 core

     in vec2 position;
     in vec3 color;

     out vec3 Color;

     void main() {
          Color = color;
          gl_Position = vec4(position, 0.0, 1.0);
     }
)glsl";

const char * fragmentSource = R"glsl(
     #version 150 core

     in vec3 Color;

     out vec4 outColor;

     void main() {
          outColor = vec4(Color, 1.0);
     }
)glsl";

GLuint shaderProgram,
     fragmentShader,
     vertexShader,
     vbo,
     vao,
     ebo;

void DebugState::begin(void) {

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

     // Shaders
     // Vertex...
     vertexShader = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertexShader, 1, &vertexSource, NULL);
     glCompileShader(vertexShader);

     GLint status;
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
     if(status != GL_TRUE) {
          char buffer[512];
          glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
          RuntimeCore::log(ERROR, "There was a fatal error while trying to compile a shader! Please see more information below...");
          cout << buffer << endl;
          RuntimeCore::stop();
     }

     // Fragment
     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
     glCompileShader(fragmentShader);

     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
     if(status != GL_TRUE) {
          char buffer[512];
          glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
          RuntimeCore::log(ERROR, "There was a fatal error while trying to compile a shader! Please see more information below...");
          cout << buffer << endl;
          RuntimeCore::stop();
     }

     shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
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

void DebugState::instruction(void) {
     if(RuntimeCore::events->keyJustPressed(SDLK_ESCAPE))
          RuntimeCore::stop();
}

void DebugState::renderContext(void) {
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DebugState::onGUI(void) {
     RuntimeCore::gui->debugEngineControl();
     RuntimeCore::gui->debugInputStatus();
}

void DebugState::end(void) {
     glDeleteProgram(shaderProgram);
     glDeleteShader(fragmentShader);
     glDeleteShader(vertexShader);
     glDeleteBuffers(1, &vbo);
     glDeleteVertexArrays(1, &vao);
     RuntimeCore::log(SUCCESS, "\"Debug\" engine state ended successfully.");
}

#endif
