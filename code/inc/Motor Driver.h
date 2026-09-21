#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038 */

typedef enum
{
    MOTOR_DRIVER_DIRECTION_STOP = 0,
    MOTOR_DRIVER_DIRECTION_FORWARD,
    MOTOR_DRIVER_DIRECTION_REVERSE
} MotorDriver_Direction_t;

typedef struct
{
    bool enabled;
    MotorDriver_Direction_t direction;
    uint16_t pwm_duty;
} MotorDriver_Status_t;

void MotorDriver_Init(void);
void MotorDriver_DriveMotor(MotorDriver_Direction_t dir, bool enable);
void MotorDriver_StopMotor(void);
MotorDriver_Status_t MotorDriver_GetStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTOR_DRIVER_H */
