#include "error_handler.h"

static uint8_t error_flags = 0;
static uint8_t last_error_code = 0;

void ErrorHandler_Init(void) { error_flags = 0; last_error_code = 0; }
void ErrorHandler_SetError(uint8_t code) { error_flags = 1; last_error_code = code; }
void ErrorHandler_Clear(void) { error_flags = 0; last_error_code = 0; }
uint8_t ErrorHandler_GetError(void) { return error_flags; }
