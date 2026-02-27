#ifndef LED_STATUS_H
#define LED_STATUS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool power_led;
    bool pos_leds[6];
} LedStates_t;

void LEDStatus_Init(void);
void LEDStatus_SetPower(bool on);
void LEDStatus_SetPosition(uint8_t logical_pos);
void LEDStatus_ClearAll(void);

#endif // LED_STATUS_H
