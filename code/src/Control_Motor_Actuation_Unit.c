#include "Control_Motor_Actuation_Unit.h"
// Responsibility 1: Direct the motor to position the HVAC flap to the target from a valid command.
void Control_Motor_Actuation_Unit_resp_1(ControlMotorActuationUnitData* data, uint8_t command) {
    data->target_flap_position = command;
    data->motor_state = CMAU_MOTOR_POSITIONING; // TRACE: "On command, validate and initiate motor control sequence."
}
// Responsibility 2: Stop the motor when target is reached or on invalid/unsafe ADC values.
void Control_Motor_Actuation_Unit_resp_2(ControlMotorActuationUnitData* data, uint8_t cur_pos) {
    if (cur_pos == data->target_flap_position || data->adc_safety_status) {
        data->motor_state = CMAU_IDLE;
        data->target_reached = 1;
    }
}
// Responsibility 3: Implement logic for correct motor actuation and safety shutdowns.
void Control_Motor_Actuation_Unit_resp_3(ControlMotorActuationUnitData* data) {
    if (data->shutdown_flag || data->adc_safety_status) {
        data->motor_state = CMAU_ERROR_RECOVERY;
        data->actuation_fault_flag = 1; // enter fail-safe
    }
}
