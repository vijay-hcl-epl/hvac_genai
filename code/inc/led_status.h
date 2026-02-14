#ifndef LED_STATUS_H
#define LED_STATUS_H
#include <stdint.h>
void LEDStatus_Init(void);
void LED_SetStatus(uint8_t pos);
void LED_SetPowerOn(void);
void LED_SetError(void);
#endif // LED_STATUS_H
