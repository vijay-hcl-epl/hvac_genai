#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include "hardware_abstraction_layer.h"

typedef enum {
    DRIVER_IDLE,
    DRIVER_ACTION,
    DRIVER_COMPLETE
} DriverState_t;

void EID_PerformOperation(int32_t target_position);
void EID_StopMotor(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
