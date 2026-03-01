// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §26-27, §29.11
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <stdint.h>
void ErrorHandler_FlagError(uint8_t code);
void ErrorHandler_ClearError(void);
void ErrorHandler_Init(void);
#endif
