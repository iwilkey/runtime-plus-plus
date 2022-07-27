#ifndef RUNTIME_SRC_CORE_H_
#define RUNTIME_SRC_CORE_H_

#include <iostream>
using namespace std;

#include "RuntimeWindow.h"
#include "RuntimeInput.h"

#define VERSION "1.0.0"

class RuntimeCore {
    public:
        RuntimeCore(int, int, char *);
        ~RuntimeCore();

        RuntimeWindow * getWindow(void);
        RuntimeInput * getInput(void);
        void stop(void);

    private:
        RuntimeWindow * window = nullptr;
        RuntimeInput * input = nullptr;
        bool running = false;

        void run(void);
};

#endif // RUNTIME_SRC_CORE_H_