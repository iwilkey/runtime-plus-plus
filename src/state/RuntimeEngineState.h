#ifndef RUNTIME_SRC_STATE_ENGINESTATE_H_
#define RUNTIME_SRC_STATE_ENGINESTATE_H_

#include <iostream>
using namespace std;

class RuntimeEngineState {
    public:
        RuntimeEngineState(string);
        RuntimeEngineState();
        virtual ~RuntimeEngineState();

        virtual void begin(void) = 0;
        virtual void instruction(void) = 0;
        virtual void renderContext(void) = 0;
        virtual void onGUI(void) = 0;
        virtual void end(void) = 0;

        string getName(void);

    private:
        string name;
};

#endif
