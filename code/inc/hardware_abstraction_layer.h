#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>

void HAL_Init(void);
uint16_t HAL_ReadADC(void);
void HAL_SetRelay(uint8_t state);
void HAL_SetLED(uint8_t status);
uint8_t HAL_GetLEDStatus(void);

#endif // HARDWARE_ABSTRACTION_LAYER_H
