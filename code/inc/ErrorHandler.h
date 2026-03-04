#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "SystemTypes.h"

void ErrorHandler_Trigger(enum ErrorType code);
void ErrorHandler_Clear(void);

#endif // ERROR_HANDLER_H
