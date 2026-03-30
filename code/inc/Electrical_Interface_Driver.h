#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>

// State Machine
typedef enum {
    EID_RESET,
    EID_DRIVE_MOTOR,
    EID_READ_FEEDBACK,
    EID_IDLE
} EidState_t;

void ElectricalInterfaceDriver_Init(void);
void ElectricalInterfaceDriver_DriveMotorTo(uint8_t pos);
uint16_t ElectricalInterfaceDriver_ReadADC(void);
uint8_t ElectricalInterfaceDriver_ReadGPIO(void);
uint8_t ElectricalInterfaceDriver_GetLEDStatus(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
