/* GPIO.h - Mock HAL for GPIOs (motor, LEDs, etc.) */
#ifndef GPIO_H
#define GPIO_H
#include <stdbool.h>
void GPIO_SetMotorEnable(bool enable);
void GPIO_SetMotorDir(bool up);
void GPIO_SetStatusLED(bool on);
void GPIO_SetGreenLED(uint8_t index, bool on);
void GPIO_SetAllGreenLEDs(bool on);
#endif
