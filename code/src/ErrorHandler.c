#include "ErrorHandler.h"
#include "StatusIndicator.h"
static ErrorCode lastError = ERROR_NONE;

void ErrorHandler_Init(void) {
    lastError = ERROR_NONE;
}

void ErrorHandler_Report(ErrorCode code) {
    lastError = code;
    StatusIndicator_SetStatus(STATUS_ERROR);
}
