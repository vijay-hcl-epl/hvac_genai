#ifndef LED_STATUS_H
#define LED_STATUS_H

#include <stdint.h>
#include <stdbool.h>

void LEDStatus_Init(void);
void LEDStatus_SetPower(bool on);
void LEDStatus_SetPosition(uint8_t pos);

#endif /* LED_STATUS_H */
