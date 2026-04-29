#include "flap_control_logic.h"
#include "hardware_abstraction.h"
#include "input_handler.h"

#define POSITION_MAX 5
#define ADC_OUT_OF_RANGE 0xFFFF

static uint8_t target_position = 0xFF;
static uint8_t actual_position = 0xFF;
static flap_state_t logic_state = FLAP_STATE_IDLE;
static uint16_t calibration_values[POSITION_MAX] = {100, 200, 300, 400, 500};

void flap_control_logic_init(void) {
    target_position = 0xFF;
    actual_position = 0xFF;
    logic_state = FLAP_STATE_IDLE;
}

void flap_control_on_valid_position(uint8_t position_idx) {
    if (logic_state == FLAP_STATE_IDLE && position_idx < POSITION_MAX) {
        target_position = position_idx;
        logic_state = FLAP_STATE_MOVING;
        hardware_abstraction_motor_set(true);
        hardware_abstraction_pwm_set(position_idx);
    }
}

void flap_control_logic_task(void) {
    uint16_t adc = hardware_abstraction_adc_read();
    // Simple mapping: closest calibration
    uint8_t closest = 0; uint16_t min_delta = 0xFFFF;
    for (uint8_t i = 0; i < POSITION_MAX; ++i) {
        uint16_t delta = (adc > calibration_values[i]) ? (adc - calibration_values[i]) : (calibration_values[i] - adc);
        if (delta < min_delta) { min_delta = delta; closest = i; }
    }
    actual_position = closest;
    // Error if adc out of calibration region (simulate as > 600)
    if (adc > 600) {
        logic_state = FLAP_STATE_ERROR;
        hardware_abstraction_motor_set(false);
        hardware_abstraction_led_set(0x0F);
        input_handler_command_complete();
        return;
    }
    if (logic_state == FLAP_STATE_MOVING && actual_position == target_position) {
        hardware_abstraction_motor_set(false);
        hardware_abstraction_led_set(1 << actual_position);
        logic_state = FLAP_STATE_AT_TARGET;
        input_handler_command_complete();
    }
}

flap_state_t flap_control_get_state(void) {
    return logic_state;
}

uint8_t flap_control_get_position(void) {
    return actual_position;
}
