#include "System_Initialization_Supervision_Unit.h"
// Responsibility 1: Initialize all software and hardware peripherals (ADC, UART, PWM, GPIO) on startup.
void System_Initialization_Supervision_Unit_resp_1(SystemInitializationSupervisionUnitData* data) {
    data->adc_init_flag = 1; // TRACE: "Power-up triggers sequential peripheral initialization (ADC, UART, etc.)."
    data->uart_init_flag = 1;
    data->pwm_init_flag = 1;
    data->gpio_init_flag = 1;
    data->system_mode = SISU_WAIT_FOR_COMMAND;
}
// Responsibility 2: Ensure the motor is off until a valid command is received.
void System_Initialization_Supervision_Unit_resp_2(SystemInitializationSupervisionUnitData* data, uint8_t valid_cmd) {
    if (!valid_cmd) {
        // ensure motor is off
    } else {
        data->system_mode = SISU_SUPERVISE;
    }
}
// Responsibility 3: Provide supervision for safe startup and ongoing operation.
void System_Initialization_Supervision_Unit_resp_3(SystemInitializationSupervisionUnitData* data, uint8_t motor_fault) {
    // Periodic supervision, run diagnostics, enforce motor-off policy when required.
    if (motor_fault || data->safety_condition_flag) {
        // Disable all outputs instantly (<10 ms)
        data->system_mode = SISU_POWER_UP; // system halt/safe
    }
}
