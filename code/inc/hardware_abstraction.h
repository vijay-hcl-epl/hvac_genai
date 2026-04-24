#ifndef HARDWARE_ABSTRACTION_H
#define HARDWARE_ABSTRACTION_H
#include <stdint.h>
#include <stdbool.h>

void HA_Init(void);
int HA_SampleADC(void);
void HA_StartMotor(bool clockwise); // true = CW, false = CCW
void HA_StopMotor(void);
void HA_SetLED(int index, int value); // 1=on, 0=off

#endif // HARDWARE_ABSTRACTION_H
