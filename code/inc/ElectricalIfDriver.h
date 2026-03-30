#ifndef ELECTRICAL_IF_DRIVER_H
#define ELECTRICAL_IF_DRIVER_H
#include <stdint.h>
void ElectricalIfDriver_Init(void);
uint16_t ElectricalIfDriver_ReadADC(void);
void ElectricalIfDriver_SetGreenLED(uint8_t pos);
void ElectricalIfDriver_StopMotor(void);
void ElectricalIfDriver_MoveMotor(uint8_t direction);
void ElectricalIfDriver_UARTSend(uint8_t data);
uint8_t ElectricalIfDriver_UARTReceive(void);
#endif // ELECTRICAL_IF_DRIVER_H
