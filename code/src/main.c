#include "motor_flap_actuation_and_positioning_unit.h"
#include "position_sensing_and_monitoring_unit.h"
#include "system_initialization_and_safety_unit.h"
#include "input_command_handling_unit.h"
#include "led_status_and_feedback_unit.h"

int main(void)
{
    // Initialize all module state variables as per DOORS LLDs
    MotorFlapData_t motor_flap = {0};
    PositionSensingData_t position_monitor = {0};
    SystemInitSafetyData_t system_init = {0};
    InputCommandData_t input_command = {0};
    LedStatusData_t led_status = {0};

    // System initialization
    system_init_resp_1(&system_init);

    // Main deterministic and repeatable loop
    while (1) {
        // Sample position
        position_sensing_resp_1(&position_monitor, position_monitor.adc_result);

        // Handle input commands
        input_command_resp_1(&input_command, input_command.uart_buffer);
        input_command_resp_2(&input_command);

        // Apply command to actuation logic
        if (input_command.command_valid) {
            motor_flap_resp_1(&motor_flap, input_command.flap_target, position_monitor.filtered_position);
        }
        motor_flap_resp_2(&motor_flap, position_monitor.filtered_position);
        motor_flap_resp_3(&motor_flap);
        motor_flap_resp_4(&motor_flap, position_monitor.filtered_position);
        motor_flap_resp_5(&motor_flap, position_monitor.filtered_position);

        // System safety: if ADC invalid, ensure motor off
        system_init_resp_2(&system_init, position_monitor.adc_valid);

        // LED status feedback
        led_status_resp_1(&led_status, system_init.init_done);
        led_status_resp_2(&led_status, motor_flap.adc_position, position_monitor.adc_valid);
    }
    return 0;
}
