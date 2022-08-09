#include "NewRuntimeState.h"
#include "../src/core/RuntimeCore.h"

int main(int argc, char ** argv) {
    NewRuntimeState entryState;
    RuntimeCore core(&entryState, 1280, 720, (char *)"New Runtime++ Project");
}
