#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H

#include <stdint.h>
#include <stdbool.h>
#include "motor_driver.h"

uint16_t HWAbstraction_ReadADC(void);
void HWAbstraction_SetMotorDirection(motor_direction_t dir);
void HWAbstraction_SetMotorPWM(uint8_t duty);
void HWAbstraction_SetPowerLED(bool on);
void HWAbstraction_SetPositionLED(uint8_t idx, bool on);

#endif // HW_ABSTRACTION_H
