#ifndef RUNTIME_PROJECT_NEW_RUNTIME_STATE_H_
#define RUNTIME_PROJECT_NEW_RUNTIME_STATE_H_

#include <iostream>
using namespace std;

#include "../src/state/RuntimeEngineState.h"

class NewRuntimeState : public RuntimeEngineState {
    public:
        NewRuntimeState();
        void onBegin(void) override;
        void onInstruction(void) override;
        void glRender(void) override;
        void guiRender(void) override;
        void onEnd(void) override;
    private:
};

#endif
