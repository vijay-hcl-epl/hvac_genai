#ifndef ACTUATOR_DRIVER_H
#define ACTUATOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define MOTOR_DIR_CW    0
#define MOTOR_DIR_CCW   1

// Actuator Driver APIs
void ActuatorDrv_Init(void);
void ActuatorDrv_Move(bool enable, uint8_t direction);
void ActuatorDrv_Stop(void);

#endif // ACTUATOR_DRIVER_H
