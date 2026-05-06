#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

void LEDStatusHandler_Init(void);
void LEDStatusHandler_SetPowerLED(bool on);
void LEDStatusHandler_SetGreenLED(uint8_t position);
void LEDStatusHandler_IndicateError(void);

#endif // LED_STATUS_HANDLER_H
