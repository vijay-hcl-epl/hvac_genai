#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>
void ErrorHandler_Init(void);
void ErrorHandler_Report(uint8_t errorCode);
#endif
