#ifndef RUNTIME_SRC_PROCESS_RPROCESS_CC_
#define RUNTIME_SRC_PROCESS_RPROCESS_CC_

#include "RProcess.h"
#include "../core/RuntimeCore.h"

RProcess::RProcess() {
    this->name = "Untitled RProcess";
    this->secondsRuntime = 0.0f;
    RuntimeCore::log(NOTICE, "A new Runtime++ process \"" 
        + this->name + "\" has been constructed that will run for " + to_string(this->secondsRuntime));
}

RProcess::RProcess(string name, double secondsRuntime) {
    this->name = name;
    this->secondsRuntime = secondsRuntime;
    RuntimeCore::log(NOTICE, "A new Runtime++ process \"" 
        + this->name + "\" has been constructed that will run for " + to_string(this->secondsRuntime));
}

RProcess::~RProcess() {
    RuntimeCore::log(NOTICE, "The Runtime++ process \""  + this->name + "\" has been deconstructed");
}

void RProcess::tick(double dt) {
    this->secondsRuntime -= dt;
}

double RProcess::getCurrentSeconds(void) {
    return this->secondsRuntime;
}

#endif