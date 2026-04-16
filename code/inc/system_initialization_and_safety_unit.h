#ifndef SYSTEM_INITIALIZATION_AND_SAFETY_UNIT_H
#define SYSTEM_INITIALIZATION_AND_SAFETY_UNIT_H

#include <stdint.h>
#include <stdbool.h>

// Internal Data Design
typedef struct {
    bool init_done;
    uint8_t led_state;
    MotorState_e motor_state;
} SystemInitSafetyData_t;

void system_init_resp_1(SystemInitSafetyData_t *data); // System initialize peripherals
void system_init_resp_2(SystemInitSafetyData_t *data, bool adc_valid); // Stop motor if ADC out of expected range

#endif
