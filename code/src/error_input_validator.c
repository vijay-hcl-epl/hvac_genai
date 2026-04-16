#include "error_input_validator.h"
#include <string.h>

void error_input_validator_resp_1(error_input_validator_t *ctx) {
    /* Poll/interrupt UART and ADC for updates; set validity flags each cycle. */
    ctx->uart_input_valid = 1u;
    ctx->adc_value_valid = (ctx->adc_reading_latest <= 4095u) ? 1u : 0u;
}

void error_input_validator_resp_2(error_input_validator_t *ctx) {
    /* On invalid UART: clear input buffer, set error flag. */
    if(ctx->uart_input_valid == 0u) {
        (void)memset(ctx->uart_rx_buffer, 0, sizeof(ctx->uart_rx_buffer));
        ctx->error_log |= (1u << 0);
    }
}

void error_input_validator_resp_3(error_input_validator_t *ctx) {
    /* On abnormal ADC: set safe state flag, disable/control motor accordingly. */
    if(ctx->adc_value_valid == 0u) {
        ctx->system_safe_state = 0u; /* unsafe */
        ctx->motor_enable_flag = 0u;
        ctx->error_log |= (1u << 1);
    } else {
        ctx->system_safe_state = 1u;
    }
}
