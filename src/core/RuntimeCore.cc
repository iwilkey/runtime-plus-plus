#ifndef RUNTIME_SRC_CORE_CC_
#define RUNTIME_SRC_CORE_CC_

#include "RuntimeCore.h"

RuntimeCore::RuntimeCore(int width, int height, char * title) {
    RuntimeWindow window(width, height, title);
    this->window = &window;
    RuntimeInput input;
    this->input = &input;
}

RuntimeCore::~RuntimeCore() {}

RuntimeWindow * RuntimeCore::getWindow(void) {
    return this->window;
}

RuntimeInput * RuntimeCore::getInput(void) {
    return this->input;
}

// Main engine loop lives in here.
void RuntimeCore::run(void) {
    this->running = true;
    while(this->running) {
        stop();
    }
}

void RuntimeCore::stop(void) {
    this->running = false;
}

int main(void) {
    RuntimeCore core(1080, 720, (char *)"Runtime");
}

#endif