// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §29.11, User Manual GPIO section
#ifndef STATUS_OUTPUT_IF_H
#define STATUS_OUTPUT_IF_H
#include <stdint.h>
void StatusOutputIF_SetStatus(uint8_t state);
void StatusOutputIF_Init(void);
#endif
