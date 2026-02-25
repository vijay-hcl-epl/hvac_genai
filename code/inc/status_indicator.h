#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

#include <stdint.h>
#include <stdbool.h>

void StatusIndicator_Init(void);
void StatusIndicator_SetPowerLed(bool enable);
void StatusIndicator_SetPositionLed(uint8_t position);

#endif // STATUS_INDICATOR_H
