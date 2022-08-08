#ifndef RUNTIME_SRC_STATE_ENGINESTATE_CC_
#define RUNTIME_SRC_STATE_ENGINESTATE_CC_

#include "RuntimeEngineState.h"
#include "../core/RuntimeCore.h"

RuntimeEngineState::RuntimeEngineState() {
    this->name = "Untitled Scene";
}

RuntimeEngineState::RuntimeEngineState(string name) {
    this->name = name;
    RuntimeCore::log(SUCCESS, "Runtime++ engine state \"" + name + "\" has been constructed.");
}

RuntimeEngineState::~RuntimeEngineState() {
    RuntimeCore::log(SUCCESS, "Runtime++ engine state \"" + this->name + "\" has been destructed.");
}

string RuntimeEngineState::getName(void) {
    return this->name;
}

#endif
