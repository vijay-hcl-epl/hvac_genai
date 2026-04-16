#include "system_initialization_and_safety_unit.h"
#include "motor_flap_actuation_and_positioning_unit.h"

// System initializes all peripherals on power-up with motor off and sets LED outputs.
void system_init_resp_1(SystemInitSafetyData_t *data) {
    // Set flags, default states.
    data->init_done = true;
    data->led_state = 0;
    data->motor_state = MOTOR_STATE_OFF;
}

// Stop the motor if ADC readings are out of expected range
void system_init_resp_2(SystemInitSafetyData_t *data, bool adc_valid) {
    if (!adc_valid) {
        data->motor_state = MOTOR_STATE_OFF;
    }
}
