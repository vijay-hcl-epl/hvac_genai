#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>
void LED_Init(void);
void LED_PowerOn(void);
void LED_UpdatePosition(int pos);
#endif // LED_DRIVER_H
