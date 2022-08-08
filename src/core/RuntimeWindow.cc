#ifndef RUNTIME_SRC_CORE_WINDOW_CC_
#define RUNTIME_SRC_CORE_WINDOW_CC_

#include "RuntimeWindow.h"
#include "RuntimeCore.h"

RuntimeWindow::RuntimeWindow() {}

RuntimeWindow::RuntimeWindow(int width, int height, char * title) {

    this->width = width;
    this->height = height;
    this->title = title;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("[ERROR] %s\n", SDL_GetError());
        return;
    }
    RuntimeCore::log(SUCCESS, "SDL initialized successfully!");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    RuntimeCore::log(NOTICE, "SDL OpenGL attributes initialized successfully.");

    string glslVersion = "",
        openGLVersion = "";
    #ifdef __APPLE__
        // GL 3.2 Core + GLSL 150
        glslVersion = "#version 150";
        SDL_GL_SetAttribute( // required on Mac OS
            SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
        );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        openGLVersion = "4.1";
    #elif __linux__
        // GL 3.2 Core + GLSL 150
        glslVersion = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        openGLVersion = "4.3";
    #elif _WIN32
        // GL 3.0 + GLSL 130
        glslVersion = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        openGLVersion = "3.2";
    #endif
    RuntimeCore::log(NOTICE, "GLSL version inferred successfully. GLSL version: " + glslVersion);
    RuntimeCore::log(NOTICE, "OpenGL version inferred successfully. OpenGL version: " + openGLVersion);

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_ALLOW_HIGHDPI
    );

    this->window = SDL_CreateWindow(
        this->title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->width,
        this->height,
        windowFlags
    );
    this->aspectRatio = ((float)this->width) / this->height;
    RuntimeCore::log(NOTICE, "Runtime++ window handle created successfully.");

    SDL_SetWindowMinimumSize(window, 500, 300);

    this->glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);

    SDL_GL_SetSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        RuntimeCore::log(ERROR, "Couldn't initialize GLAD!");
        exit(-1);
    } else RuntimeCore::log(SUCCESS, "GLAD initialized successfully!");

    // glViewport(0, 0, this->width, this->height);

    // Init IMGUI in the window context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    RuntimeCore::log(NOTICE, "ImGUI context created successfully.");
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    RuntimeCore::log(NOTICE, "ImGUI OpenGL context ported to SDL2.");
    ImGui_ImplOpenGL3_Init(glslVersion.c_str());
    RuntimeCore::log(NOTICE, "ImGUI OpenGL initialized.");

    RuntimeCore::log(SUCCESS, "RuntimeWindow object construction complete!");
}

RuntimeWindow::~RuntimeWindow() {
    RuntimeCore::log(SUCCESS, "RuntimeWindow object destruction complete!");
}

float RuntimeWindow::getAspectRatio(void) {
    return this->aspectRatio;
}

void RuntimeWindow::setWidth(int width) {
    if(width <= 0) {
        RuntimeCore::log(ERROR, "You cannot set the window width to less than or equal to zero!");
        return;
    }
    this->width = width;
    this->aspectRatio = ((float)this->width) / this->height;
}

void RuntimeWindow::setHeight(int height) {
    if(height <= 0) {
        RuntimeCore::log(ERROR, "You cannot set the window height to less than or equal to zero!");
        return;
    }
    this->height = height;
    this->aspectRatio = ((float)this->width) / this->height;
}

SDL_Window * RuntimeWindow::getWindow(void) {
    return this->window;
}

SDL_GLContext RuntimeWindow::getGlContext(void) {
    return this->glContext;
}

int RuntimeWindow::getWidth(void) {
    return this->width;
}

int RuntimeWindow::getHeight(void) {
    return this->height;
}

char * RuntimeWindow::getTitle(void) {
    return this->title;
}

#endif
