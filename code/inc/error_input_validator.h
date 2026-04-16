#ifndef ERROR_INPUT_VALIDATOR_H
#define ERROR_INPUT_VALIDATOR_H

#include <stdint.h>

typedef struct {
    uint8_t uart_input_valid;
    uint8_t adc_value_valid;
    uint8_t system_safe_state;
    uint8_t uart_rx_buffer[8];
    uint16_t adc_reading_latest;
    uint8_t motor_enable_flag;
    uint32_t error_log;
} error_input_validator_t;

typedef enum {
    CHECKING_INPUTS,
    INPUTS_OK,
    INVALID_DETECTED
} inputs_state_e;

typedef enum {
    CHECKING_ADC,
    ADC_OK,
    ADC_INVALID
} adc_state_e;

typedef enum {
    CONTROL_SAFE_STATE,
    SYSTEM_SAFE,
    SYSTEM_UNSAFE
} safe_state_e;

void error_input_validator_resp_1(error_input_validator_t *ctx);
void error_input_validator_resp_2(error_input_validator_t *ctx);
void error_input_validator_resp_3(error_input_validator_t *ctx);

#endif
