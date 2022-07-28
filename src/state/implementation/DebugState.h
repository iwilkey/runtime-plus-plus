#ifndef RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_H_
#define RUNTIME_SRC_STATE_IMPLEMENTATION_DEBUG_H_

#include <iostream>
using namespace std;

#include "../RuntimeEngineState.h"

class DebugState : public RuntimeEngineState {
    public:
        DebugState();

        void begin(void) override;
        void instruction(void) override;
        void onGUI(void) override;
        void end(void) override;

    private:
        typedef RuntimeEngineState super;
};

#endif