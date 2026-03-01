#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>
typedef enum { MOTOR_DIR_OFF = 0, MOTOR_DIR_CW, MOTOR_DIR_CCW } MotorDir_t;
void MotorControl_Init(void);
void MotorControl_Start(MotorDir_t dir);
void MotorControl_Stop(void);
uint8_t MotorControl_IsActive(void);
#endif /* MOTOR_CONTROL_H */
