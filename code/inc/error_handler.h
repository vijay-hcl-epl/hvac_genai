#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>
enum {
    ERROR_NONE=0,
    ERROR_INVALID_CMD=1,
    ERROR_ADC_RANGE=2
};
void ErrorHandler_Init(void);
void ErrorHandler_SetError(uint8_t code);
void ErrorHandler_ClearError(uint8_t code);
uint8_t ErrorHandler_GetError(void);
#endif
