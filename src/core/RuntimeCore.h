#ifndef RUNTIME_SRC_CORE_CORE_H_
#define RUNTIME_SRC_CORE_CORE_H_

#include <iostream>
#include <time.h>
#include <chrono>
using namespace std;

#include "../utils/RuntimeUtilities.h"
#include "RuntimeWindow.h"
#include "../process/RuntimeProcessManager.h"
#include "RuntimeEvents.h"
#include "../gfx/RuntimeGUI.h"
#include "../gfx/RuntimeRenderer.h"
#include "../state/RuntimeEngineState.h"

enum LogType {
    SUCCESS,
    NOTICE,
    ERROR
};

class RuntimeCore {
    public:
        RuntimeCore(RuntimeEngineState *, int, int, char *);
        ~RuntimeCore();

        const static string version;

        static bool running;
        static unsigned int targetFPS;
        static double deltaTime;

        static RuntimeUtilities * utilities;
        static RuntimeWindow * window;
        static RuntimeProcessManager * processes;
        static RuntimeEvents * events;
        static RuntimeGUI * gui;
        static RuntimeRenderer * renderer;
        static RuntimeEngineState * currentState;

        static void setState(RuntimeEngineState *);
        static void log(LogType, string);
        static void stop(void);

    private:
        void run(void);
};

#endif // RUNTIME_SRC_CORE_H_
