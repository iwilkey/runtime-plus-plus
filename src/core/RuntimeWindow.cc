#ifndef RUNTIME_SRC_WINDOW_CC_
#define RUNTIME_SRC_WINDOW_CC_

#include "RuntimeWindow.h"

RuntimeWindow::RuntimeWindow(int width, int height, char * title) {

    this->width = width;
    this->height = height;
    this->title = title;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("[ERROR] %s\n", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    string glslVersion = "";
    #ifdef __APPLE__
        // GL 3.2 Core + GLSL 150
        glslVersion = "#version 150";
        SDL_GL_SetAttribute( // required on Mac OS
            SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
        );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    #elif __linux__
        // GL 3.2 Core + GLSL 150
        glslVersion = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    #elif _WIN32
        // GL 3.0 + GLSL 130
        glslVersion = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    #endif

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

    SDL_SetWindowMinimumSize(window, 500, 300);

    this->glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);

    SDL_GL_SetSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        cerr << "[ERROR] Couldn't initialize GLAD!" << std::endl;
    else cout << "[INFO] GLAD initialized.\n";

    glViewport(0, 0, this->width, this->height);

    // Init IMGUI in the window context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glslVersion.c_str());

    // SDL window created and IMGUI is ready.
}

RuntimeWindow::~RuntimeWindow() {}

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