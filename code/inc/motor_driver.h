#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIR_STOP = 0,
    MOTOR_DIR_FWD,
    MOTOR_DIR_REV
} motor_dir_t;

typedef struct {
    bool enabled;
    motor_dir_t dir;
    uint8_t pwm_duty;
} motor_driver_t;

void motor_driver_init(motor_driver_t *inst);
void motor_drive(motor_driver_t *inst, motor_dir_t dir, bool enable, uint8_t pwm);
void motor_stop(motor_driver_t *inst);
bool motor_driver_status(const motor_driver_t *inst);

#endif /* MOTOR_DRIVER_H */
