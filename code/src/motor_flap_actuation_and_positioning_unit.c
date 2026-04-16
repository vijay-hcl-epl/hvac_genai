#include "motor_flap_actuation_and_positioning_unit.h"

// Move flap to requested position based on user command.
void motor_flap_resp_1(MotorFlapData_t *data, uint16_t user_command, uint16_t adc_feedback) {
    data->target_position = user_command;
    if (adc_feedback < data->target_position) {
        data->direction = 0; // CW
        data->motor_state = MOTOR_STATE_ON_CW;
    } else if (adc_feedback > data->target_position) {
        data->direction = 1; // CCW
        data->motor_state = MOTOR_STATE_ON_CCW;
    } else {
        data->motor_state = MOTOR_STATE_OFF;
    }
}

// Stop the motor once flap reaches the target position.
void motor_flap_resp_2(MotorFlapData_t *data, uint16_t adc_feedback) {
    if (adc_feedback == data->target_position) {
        data->motor_state = MOTOR_STATE_OFF;
    }
}

// Support movement in clockwise and anti-clockwise directions via motor control.
void motor_flap_resp_3(MotorFlapData_t *data) {
    if (data->direction == 0) {
        data->motor_state = MOTOR_STATE_ON_CW;
    }
    else if (data->direction == 1) {
        data->motor_state = MOTOR_STATE_ON_CCW;
    }
}

// Support discrete flap positions mapped by ADC values in software.
void motor_flap_resp_4(MotorFlapData_t *data, uint16_t adc_feedback) {
    data->adc_position = adc_feedback;
    // Example quantization (exact mapping should be literal from LLD if specified)
    if (adc_feedback < 100) data->adc_position = 0;
    else if (adc_feedback < 200) data->adc_position = 1;
    else if (adc_feedback < 300) data->adc_position = 2;
    else if (adc_feedback < 400) data->adc_position = 3;
    // ... add further mappings per explicit LLD if given
}

// Stop the motor if ADC readings are out of range.
void motor_flap_resp_5(MotorFlapData_t *data, uint16_t adc_feedback) {
    if ((adc_feedback < 0) || (adc_feedback > 1023)) { // Assuming 10-bit ADC
        data->adc_valid = false;
        data->motor_state = MOTOR_STATE_OFF;
    } else {
        data->adc_valid = true;
    }
}
