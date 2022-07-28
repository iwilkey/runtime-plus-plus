#ifndef RUNTIME_SRC_GFX_RENDERER_H_
#define RUNTIME_SRC_GFX_RENDERER_H_

#include <iostream>
using namespace std;

#include <glad/glad.h>
#include <SDL2/SDL.h>

class RuntimeRenderer {
    public:
        RuntimeRenderer();
        ~RuntimeRenderer();

        
        void setClearColorRGB1(float, float, float);
        void setClearColorRGB255(float, float, float);

        void clear(void);
        void draw(void);
        void swapGLBuffers(void);
        
    private:
};

#endif