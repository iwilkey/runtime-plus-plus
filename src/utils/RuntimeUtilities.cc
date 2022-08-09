#ifndef RUNTIME_SRC_UTILS_UTILITIES_CC_
#define RUNTIME_SRC_UTILS_UTILITIES_CC_

#include "RuntimeUtilities.h"
#include "../core/RuntimeCore.h"

RuntimeUtilities::RuntimeUtilities() {
    RuntimeCore::log(SUCCESS, "Runtime++ utilities object constructed.");
}

RuntimeUtilities::~RuntimeUtilities() {
    RuntimeCore::log(SUCCESS, "Runtime++ utilities object deconstructed.");
}

string RuntimeUtilities::loadStringFromFile(string path) {
    string ret;
    ifstream in;
    in.open(path);
    if(in.fail()) {
        RuntimeCore::log(ERROR, "Runtime++ is trying to load a string from a file that it cannot find! Please check the name and try again.");
        RuntimeCore::stop();
    }
    string imme;
    while(in) {
        getline(in, imme);
        ret += imme + "\n";
    }
    in.close();
    return ret;
}

#endif
