#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <stdint.h>

typedef enum { MOTOR_STOP = 0, MOTOR_CW, MOTOR_CCW } MotorDirection;

typedef struct {
    uint16_t period;
    uint16_t duty_cycle;
    MotorDirection direction;
} MotorConfig;

void Motor_init(const MotorConfig* config);
uint8_t Motor_run(MotorDirection dir, uint16_t speed);
void Motor_stop(void);
uint8_t Motor_status(void);

#endif // MOTOR_DRIVER_H
