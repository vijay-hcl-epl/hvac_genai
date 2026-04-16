#ifndef MOTOR_CONTROL_UNIT_H
#define MOTOR_CONTROL_UNIT_H

#include <stdint.h>

typedef struct {
    uint8_t motor_enable;
    uint8_t motor_direction;
    uint8_t motor_pwm;
    uint8_t target_position;
    uint8_t current_position;
    uint8_t moving;
    uint8_t at_target;
    uint8_t fault_detected;
} motor_control_unit_t;

typedef enum {
    MOTOR_IDLE,
    MOTOR_ACTIVE,
    FAULT_DETECTED
} motor_state_e;

typedef enum {
    WAITING_FOR_COMMAND,
    COMMAND_RECEIVED,
    MOVING_TO_TARGET
} motor_cmd_state_e;

typedef enum {
    DIRECTION_CW,
    DIRECTION_CCW
} motor_direction_e;

void motor_control_unit_resp_1(motor_control_unit_t *ctx);
void motor_control_unit_resp_2(motor_control_unit_t *ctx);
void motor_control_unit_resp_3(motor_control_unit_t *ctx);
void motor_control_unit_resp_4(motor_control_unit_t *ctx);

#endif
