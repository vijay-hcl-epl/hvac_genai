#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>
void LEDStatusHandler_Init(void);
void LEDStatusHandler_SetPowerLED(bool state);
void LEDStatusHandler_SetPositionLED(uint8_t position);
void LEDStatusHandler_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
