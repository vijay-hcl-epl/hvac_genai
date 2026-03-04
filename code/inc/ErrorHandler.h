/* ErrorHandler.h - Error detection and handling (feedback/command errors) */
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdbool.h>

void ErrorHandler_Init(void);
void ErrorHandler_Handle(void);
bool ErrorHandler_ErrorDetected(void);

#endif /* ERROR_HANDLER_H */
