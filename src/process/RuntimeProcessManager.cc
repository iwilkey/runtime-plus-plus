#ifndef RUNTIME_SRC_PROCESS_PROCESSMANAGER_CC_
#define RUNTIME_SRC_PROCESS_PROCESSMANAGER_CC_

#include "RuntimeProcessManager.h"
#include "../core/RuntimeCore.h"

RuntimeProcessManager::RuntimeProcessManager() {
    RuntimeCore::log(SUCCESS, "Runtime++ process manager object constructed!");
}

RuntimeProcessManager::~RuntimeProcessManager() {
    RuntimeCore::log(SUCCESS, "Runtime++ process manager object deconstructed!");
}

void RuntimeProcessManager::addProcess(RProcess * process) {
    if(RuntimeCore::utilities->vectorContains(this->activeProcesses, process)) {
        RuntimeCore::log(ERROR, "You cannot add a RProcess that is already active.");
        return;
    }
    process->begin();
    this->activeProcesses.push_back(process);
}

void RuntimeProcessManager::removeProcess(RProcess * process) {
    long long int in = RuntimeCore::utilities->vectorContains(this->activeProcesses, process);
    if(in == -1) {
        RuntimeCore::log(NOTICE, "You are trying to delete an RProcess that is not active.");
        return;
    }
    process->end();
    RuntimeCore::utilities->vectorErase(this->activeProcesses, process);
}

vector<RProcess *> dead;
void RuntimeProcessManager::tick(void) {
    if(this->activeProcesses.size() == 0) return;
    dead.clear();
    for(int i = 0; i < this->activeProcesses.size(); i++) {
        activeProcesses[i]->tick(RuntimeCore::deltaTime);
        if(activeProcesses[i]->getCurrentSeconds() <= 0.0f) {
            dead.push_back(activeProcesses[i]);
            continue;
        }
        activeProcesses[i]->during();
    }
    for(int i = 0; i < dead.size(); i++)
        removeProcess(dead[i]);
}

#endif