#ifndef RUNTIME_SRC_PROCESS_RPROCESS_H_
#define RUNTIME_SRC_PROCESS_RPROCESS_H_

#include <iostream>
using namespace std;

class RProcess {
    public:

        RProcess(string, double);
        RProcess();
        virtual ~RProcess();

        virtual void begin(void) = 0;
        virtual void during(void) = 0;
        virtual void end(void) = 0;

        void tick(double dt);
        double getCurrentSeconds(void);

    private:
        string name;
        double secondsRuntime; // How long will the process run (in seconds)? (Neg for indefinite).
};

#endif