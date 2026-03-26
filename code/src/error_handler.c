#include "error_handler.h"
#include "status_output_if.h"
static uint8_t error_flags = ERROR_NONE;
static uint8_t last_error_code = ERROR_NONE;
void ErrorHandler_Init(void) {
    error_flags = ERROR_NONE;
    last_error_code = ERROR_NONE;
}
void ErrorHandler_SetError(uint8_t code) {
    error_flags |= (1<<code);
    last_error_code = code;
    StatusOutputIf_SetStatus(STATUS_ERR);
}
void ErrorHandler_ClearError(uint8_t code) {
    error_flags &= ~(1<<code);
    if (error_flags == ERROR_NONE) StatusOutputIf_SetStatus(STATUS_OK);
}
uint8_t ErrorHandler_GetError(void) {
    return last_error_code;
}
