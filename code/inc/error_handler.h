#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>
void ErrorHandler_Init(void);
void ErrorHandler_SetErrorState(uint8_t flag);
void ErrorHandler_ClearErrorState(void);
#endif // ERROR_HANDLER_H
