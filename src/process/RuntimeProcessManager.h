#ifndef RUNTIME_SRC_PROCESS_PROCESSMANAGER_H_
#define RUNTIME_SRC_PROCESS_PROCESSMANAGER_H_

#include <iostream>
#include <vector>
using namespace std;

#include "RProcess.h"

class RuntimeProcessManager {
    public:
        RuntimeProcessManager();
        ~RuntimeProcessManager();

        void tick(void);
        void addProcess(string, double);
        void removeProcess(string);
        int getActiveProcess(string);
        bool isActive(string);
        
    private:
        vector<RProcess> activeProcesses;
};

#endif