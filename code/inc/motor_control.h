#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <stdint.h>
typedef enum { MOTOR_DIR_CW = 0, MOTOR_DIR_CCW } MotorDir;
void MOTOR_Init(void);
void MOTOR_Run(MotorDir dir);
void MOTOR_Stop(void);
#endif // MOTOR_CONTROL_H
