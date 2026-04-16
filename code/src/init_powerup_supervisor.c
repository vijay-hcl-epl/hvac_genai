#include "init_powerup_supervisor.h"

void init_powerup_supervisor_resp_1(init_powerup_supervisor_t *ctx) {
    /* seq: On power-up, sequentially initialize ADC, UART, GPIO, PWM. */
    ctx->adc_handle = 1u; /* assume init success */
    ctx->uart_handle = 1u;
    ctx->gpio_state = 1u;
    ctx->pwm_config = 1u;
    /* state: Peripherals initialized */
    /* error: If any failed (not applicable in default stub) */
}

void init_powerup_supervisor_resp_2(init_powerup_supervisor_t *ctx) {
    /* seq: After init, explicitly clear/disable motor enable output. */
    ctx->motor_status = 0u;
}

void init_powerup_supervisor_resp_3(init_powerup_supervisor_t *ctx) {
    /* seq: Read ADC channel to capture initial potentiometer value. */
    ctx->pot_value = 0u; /* stubbed ADC read */
}

void init_powerup_supervisor_resp_4(init_powerup_supervisor_t *ctx) {
    /* seq: Set power LED ON and select corresponding position LED per initial reading */
    ctx->power_led_state = 1u;
    for (uint8_t i = 0; i < 6; ++i) {
        ctx->pos_led_state[i] = 0u;
    }
    ctx->pos_led_state[ctx->pot_value] = 1u; /* only one position led ON */
}
