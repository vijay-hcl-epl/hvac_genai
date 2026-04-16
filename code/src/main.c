#include "Feedback_Sensing_Unit.h"
#include "Output_Indication_Unit.h"
#include "Input_Handling_Unit.h"
#include "Control_Motor_Actuation_Unit.h"
#include "System_Initialization_Supervision_Unit.h"

// Module state variables
FeedbackSensingUnitData g_feedback;
OutputIndicationUnitData g_output;
InputHandlingUnitData g_input;
ControlMotorActuationUnitData g_control;
SystemInitializationSupervisionUnitData g_sis;

int main() {
    // Initialize all structures
    g_feedback.adc_min = 0;
    g_feedback.adc_max = 1023;
    g_feedback.median_index = 0;
    g_output.power_up_flag = 0;
    g_output.led_state = 0;
    g_output.last_flap_position = 0;
    g_input.is_valid = 0;
    g_input.ignore_flag = 0;
    g_input.consecutive_invalid = 0;
    g_control.motor_state = CMAU_WAIT_FOR_COMMAND;
    g_control.target_flap_position = 0;
    g_control.current_position = 0;
    g_sis.system_mode = SISU_POWER_UP;

    while(1) {
        // Sequential, deterministic order
        System_Initialization_Supervision_Unit_resp_1(&g_sis);
        Input_Handling_Unit_resp_1(&g_input);
        Input_Handling_Unit_resp_2(&g_input);
        Input_Handling_Unit_resp_3(&g_input);
        Feedback_Sensing_Unit_resp_1(&g_feedback);
        Feedback_Sensing_Unit_resp_2(&g_feedback);
        Feedback_Sensing_Unit_resp_3(&g_feedback);
        Control_Motor_Actuation_Unit_resp_1(&g_control, g_input.parsed_command);
        Control_Motor_Actuation_Unit_resp_2(&g_control, g_feedback.mapped_position);
        Control_Motor_Actuation_Unit_resp_3(&g_control);
        Output_Indication_Unit_resp_1(&g_output, g_feedback.mapped_position);
        Output_Indication_Unit_resp_2(&g_output);
        System_Initialization_Supervision_Unit_resp_2(&g_sis, g_input.is_valid);
        System_Initialization_Supervision_Unit_resp_3(&g_sis, g_control.actuation_fault_flag);
    }
    return 0;
}
