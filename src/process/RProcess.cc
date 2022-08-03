#ifndef RUNTIME_SRC_PROCESS_RPROCESS_CC_
#define RUNTIME_SRC_PROCESS_RPROCESS_CC_

#include "RProcess.h"
#include "../core/RuntimeCore.h"

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

void RProcess::setCurrentSeconds(double time) {
    this->secondsRuntime = time;
}

void RProcess::kill(void) {
    this->shouldDie = true;
}

bool RProcess::isDead(void) {
    return this->shouldDie;
}

string RProcess::getName(void) {
    return this->name;
}

#endif
