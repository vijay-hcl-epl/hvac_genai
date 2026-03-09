#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>

void ErrorHandler_Init(void);
void ErrorHandler_SetError(uint8_t code);
void ErrorHandler_Clear(void);
uint8_t ErrorHandler_GetError(void);

#endif // ERROR_HANDLER_H
