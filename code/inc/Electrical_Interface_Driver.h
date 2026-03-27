#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>

void ElectricalInterfaceDriver_Init(void);
void ElectricalInterfaceDriver_SetFlapPosition(uint8_t position);
int ElectricalInterfaceDriver_FlapAtTarget(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
