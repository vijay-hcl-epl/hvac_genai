#include "error_handler.h"

static uint8_t error_flags = ERR_NONE;

void ErrorHandler_Init(void) {
    error_flags = ERR_NONE;
}

void ErrorHandler_Set(uint8_t code) {
    error_flags |= code;
}

void ErrorHandler_Clear(void) {
    error_flags = ERR_NONE;
}

uint8_t ErrorHandler_GetFlags(void) {
    return error_flags;
}
