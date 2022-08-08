#ifndef RUNTIME_SRC_PROCESS_RPROCESS_H_
#define RUNTIME_SRC_PROCESS_RPROCESS_H_

#include <iostream>
using namespace std;

class RProcess {
    public:
        RProcess(string, double);
        ~RProcess();

        void tick(double dt);
        void kill(void);
        bool isDead(void);
        double getCurrentSeconds(void);
        void setCurrentSeconds(double);
        string getName(void);

    private:
        string name;
        double secondsRuntime; // How long will the process run (in seconds)? (Neg for indefinite).
        bool shouldDie = false;
};

#endif
