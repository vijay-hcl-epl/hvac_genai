#include "ErrorHandler.h"
#include "StatusIndicator.h"
static uint8_t last_error = 0;
void ErrorHandler_Init(void) { last_error = 0; }
void ErrorHandler_Report(uint8_t errorCode) {
    last_error = errorCode;
    StatusIndicator_SetStatus(0); // Assume OFF displays error
}
