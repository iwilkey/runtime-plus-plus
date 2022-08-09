#ifndef RUNTIME_SRC_STATE_ENGINESTATE_H_
#define RUNTIME_SRC_STATE_ENGINESTATE_H_

#include <iostream>
using namespace std;

class RuntimeEngineState {
    public:
        RuntimeEngineState(string);
        RuntimeEngineState();
        virtual ~RuntimeEngineState();

        virtual void onBegin(void) = 0;
        virtual void onInstruction(void) = 0;
        virtual void glRender(void) = 0;
        virtual void guiRender(void) = 0;
        virtual void onEnd(void) = 0;

        string getName(void);

    private:
        string name;
};

#endif
