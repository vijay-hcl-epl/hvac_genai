#ifndef LED_INDICATOR_H
#define LED_INDICATOR_H

#include <stdint.h>
#include <stdbool.h>

void LEDIndicator_Init(void);
void LEDIndicator_SetPosition(uint8_t pos);
void LEDIndicator_SetPower(bool on);

#endif // LED_INDICATOR_H
