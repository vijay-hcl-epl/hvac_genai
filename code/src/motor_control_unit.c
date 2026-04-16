#include "motor_control_unit.h"

void motor_control_unit_resp_1(motor_control_unit_t *ctx) {
    /* On command, compare current and target; select direction, set PWM enable. */
    if(ctx->target_position > ctx->current_position) {
        ctx->motor_direction = 1u; /* CW */
    } else if(ctx->target_position < ctx->current_position) {
        ctx->motor_direction = 0u; /* CCW */
    }
    ctx->motor_enable = (ctx->target_position != ctx->current_position) ? 1u : 0u;
    ctx->motor_pwm = ctx->motor_enable ? 1u : 0u;
    ctx->moving = ctx->motor_enable;
}

void motor_control_unit_resp_2(motor_control_unit_t *ctx) {
    /* Monitor feedback; when target reached, clear enable, update at_target. */
    if(ctx->current_position == ctx->target_position) {
        ctx->motor_enable = 0u;
        ctx->motor_pwm = 0u;
        ctx->at_target = 1u;
    } else {
        ctx->at_target = 0u;
    }
}

void motor_control_unit_resp_3(motor_control_unit_t *ctx) {
    /* If control logic requests, immediately issue Stop signal; log/flag if fault. */
    if(ctx->fault_detected) {
        ctx->motor_enable = 0u;
        ctx->motor_pwm = 0u;
        ctx->moving = 0u;
    }
}

void motor_control_unit_resp_4(motor_control_unit_t *ctx) {
    /* On initialization, motor defaults to OFF/Idle state until commanded. */
    ctx->motor_enable = 0u;
    ctx->motor_pwm = 0u;
    ctx->moving = 0u;
    ctx->at_target = 0u;
}
