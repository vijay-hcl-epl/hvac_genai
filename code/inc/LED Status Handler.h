#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

void LedStatusHandler_Init(void);
void LedStatusHandler_SetPowerLed(void);
void LedStatusHandler_SetLedState(uint8_t position);
void LedStatusHandler_IndicateError(void);
uint8_t LedStatusHandler_GetCurrentState(void);

#endif /* LED_STATUS_HANDLER_H */
