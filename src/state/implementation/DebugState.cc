#ifndef RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_CC_
#define RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_CC_

#include "DebugState.h"
#include "../../core/RuntimeCore.h"

DebugState::DebugState() : RuntimeEngineState("Debug") {}

void DebugState::begin(void) {
    RuntimeCore::log(SUCCESS, "Debug state loaded successfully.");
}

void DebugState::instruction(void) {

}

void DebugState::onGUI(void) {
     RuntimeCore::gui->debugEngineControl();
}

void DebugState::end(void) {
     RuntimeCore::log(SUCCESS, "\"Debug\" engine state ended successfully.");
}

#endif