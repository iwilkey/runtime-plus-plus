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

void RuntimeProcessManager::addProcess(string name, double time) {
    if(time <= 0.0f) {
        RuntimeCore::log(ERROR, "A process must active for longer than zero seconds to be created!");
        return;
    }
    if(isActive(name)) {
        RuntimeCore::log(NOTICE, "There is already a process by the name \"" + name + "\", so Runtime++ will set it's runtime to the time specified.");
        this->activeProcesses[getActiveProcess(name)].setCurrentSeconds(time);
        return;
    }
    RProcess process(name, time);
    this->activeProcesses.push_back(process);
}

int RuntimeProcessManager::getActiveProcess(string name) {
    for(int i = 0; i < this->activeProcesses.size(); i++)
        if(this->activeProcesses[i].getName() == name)
            return i;
    return -1;
}

void RuntimeProcessManager::removeProcess(string name) {
    if(!isActive(name)) {
        RuntimeCore::log(NOTICE, "You are trying to delete an RProcess that is not active.");
        return;
    }
    this->activeProcesses.erase(this->activeProcesses.begin() + getActiveProcess(name));
}

bool RuntimeProcessManager::isActive(string name) {
    for(int i = 0; i < this->activeProcesses.size(); i++) 
        if(this->activeProcesses[i].getName() == name)
            return true;
    return false;
}

vector<RProcess> dead;
void RuntimeProcessManager::tick(void) {
    if(this->activeProcesses.size() == 0) return;
    dead.clear();
    for(int i = 0; i < this->activeProcesses.size(); i++) {
        activeProcesses[i].tick(RuntimeCore::deltaTime);
        if(activeProcesses[i].getCurrentSeconds() <= 0.0f 
            || activeProcesses[i].isDead()) {
            dead.push_back(activeProcesses[i]);
            continue;
        }
    }
    for(int i = 0; i < dead.size(); i++)
        removeProcess(dead[i].getName());
}

#endif
