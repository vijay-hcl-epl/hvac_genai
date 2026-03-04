#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H
#include <stdint.h>
void StatusIndicator_Init(void);
void StatusIndicator_SetStatus(uint8_t status);
void StatusIndicator_SetPositionLed(uint8_t position);
#endif
