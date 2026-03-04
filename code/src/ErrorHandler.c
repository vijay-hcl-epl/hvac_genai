/* ErrorHandler.c - Error response implementation */
#include "ErrorHandler.h"
#include "PositionFeedback.h"
#include "MotorDriver.h"

static bool errorDetected = false;

void ErrorHandler_Init(void) {
    errorDetected = false;
}

bool ErrorHandler_ErrorDetected(void) {
    errorDetected = PositionFeedback_ErrorStatus();
    return errorDetected;
}

void ErrorHandler_Handle(void) {
    if (ErrorHandler_ErrorDetected()) {
        MotorDriver_Stop();
        // Additional handling
    }
}
