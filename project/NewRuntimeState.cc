#ifndef RUNTIME_PROJECT_NEW_RUNTIME_STATE_CC_
#define RUNTIME_PROJECT_NEW_RUNTIME_STATE_CC_

#include "NewRuntimeState.h"
#include "../src/core/RuntimeCore.h"

// How to include SOIL...
#include "../runtime-plus-plus-libraries/soil-static/SOIL.h"

#include "../runtime-plus-plus-libraries/glm-static/glm.hpp"
#include "../runtime-plus-plus-libraries/glm-static/gtc/matrix_transform.hpp"
#include "../runtime-plus-plus-libraries/glm-static/gtc/type_ptr.hpp"

NewRuntimeState::NewRuntimeState() : RuntimeEngineState("NewRuntimeState") {}

GLfloat vertices[] = {
//  Position      Color             Texcoords
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};
 // Draw rectangle with two triangles clockwise from top left (OpenGL convention).
GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
};

GLuint shaderProgram,
     vbo,
     vao,
     ebo,
     tex;

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
          in vec2 texcoord;
          out vec3 Color;
          out vec2 Texcoord;

          void main() {
               Color = color;
               Texcoord = texcoord;
               gl_Position = vec4(position, 0.0, 1.0);
          }
     )glsl");
     
     // Fragment
     RuntimeCore::renderer->addShaderSource("simple-fragment", GL_FRAGMENT_SHADER, R"glsl(
          #version 150 core
          in vec3 Color;
          in vec2 Texcoord;
          out vec4 outColor;
          uniform sampler2D tex;
          void main() {
               outColor = texture(tex, Texcoord);
          }
     )glsl");

     shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, RuntimeCore::renderer->getShader("simple-vertex"));
     glAttachShader(shaderProgram, RuntimeCore::renderer->getShader("simple-fragment"));
     glBindFragDataLocation(shaderProgram, 0, "outColor");
     glLinkProgram(shaderProgram);
     glUseProgram(shaderProgram);

     // Specify the layout of the vertex data
     GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
     glEnableVertexAttribArray(posAttrib);
     glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

     GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
     glEnableVertexAttribArray(colAttrib);
     glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

     GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
     glEnableVertexAttribArray(texAttrib);
     glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

     // Load texture
     glGenTextures(1, &tex);
     glBindTexture(GL_TEXTURE_2D, tex);

     int width, height;
     unsigned char * image = SOIL_load_image("../resources/cat.png", &width, &height, 0, SOIL_LOAD_RGBA);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
     SOIL_free_image_data(image);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
}

void NewRuntimeState::onEnd(void) {
     glDeleteProgram(shaderProgram);
     glDeleteShader(RuntimeCore::renderer->getShader("simple-fragment"));
     glDeleteShader(RuntimeCore::renderer->getShader("simple-vertex"));
     glDeleteBuffers(1, &vbo);
     glDeleteVertexArrays(1, &vao);
     glDeleteBuffers(1, &ebo);
     glDeleteTextures(1, &tex);
     RuntimeCore::log(SUCCESS, "\"Debug\" engine state ended successfully.");
}

#endif
