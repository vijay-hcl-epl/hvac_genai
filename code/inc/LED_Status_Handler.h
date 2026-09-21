#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

void LEDStatusHandler_Init(void);
void LEDStatusHandler_SetPowerLed(void);
void LEDStatusHandler_SetLedState(uint8_t position);
void LEDStatusHandler_IndicateError(void);
uint8_t LEDStatusHandler_GetCurrentState(void);

#endif /* LED_STATUS_HANDLER_H */
