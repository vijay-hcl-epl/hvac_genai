#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>

void EID_Init(void);
uint16_t EID_ReadADC(void);
void EID_SetRelay(uint8_t state);
void EID_SetLED(uint8_t status);
uint8_t EID_GetLEDStatus(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
