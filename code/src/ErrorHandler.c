#include "ErrorHandler.h"
#include "MotorDriver.h"
#include "StatusIndicator.h"

static enum ErrorType last_error = ERROR_NONE;
static bool errorSafe = false;

void ErrorHandler_Trigger(enum ErrorType code) {
    last_error = code;
    errorSafe = true;
    MotorDriver_Stop();
    StatusIndicator_Update(FLAP_POS_INVALID, true); // All LEDs off for error
}

void ErrorHandler_Clear(void) {
    last_error = ERROR_NONE;
    errorSafe = false;
    // Could restore to normal LED/status recovery
}
