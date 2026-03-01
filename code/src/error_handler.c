// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §26-27, §29.11, User Manual Error Handling
#include "error_handler.h"
static uint8_t LastErrorCode = 0;
void ErrorHandler_FlagError(uint8_t code) {
    LastErrorCode = code;
    // Drive motor output safe (call MotorDriverIF_Stop, StatusOutputIF_SetStatus)
}
void ErrorHandler_ClearError(void) {
    LastErrorCode = 0;
}
void ErrorHandler_Init(void) { LastErrorCode = 0; }
