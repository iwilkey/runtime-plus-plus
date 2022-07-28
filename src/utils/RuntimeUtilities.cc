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

#endif