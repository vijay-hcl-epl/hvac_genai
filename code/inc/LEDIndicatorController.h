#ifndef LED_INDICATOR_CONTROLLER_H
#define LED_INDICATOR_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

// LED Indicator Controller APIs
void LEDCtrl_Init(void);
void LEDCtrl_IndicatePosition(uint8_t pos);
void LEDCtrl_StatusLED_Set(bool on);

#endif // LED_INDICATOR_CONTROLLER_H
