#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

static SIM_State_t sim_state = SIM_IDLE;
static int sim_current_position = 0;

void SIM_Init(void) {
    sim_state = SIM_MONITORING;
}

void SIM_ProcessADC(int adc_value) {
    // Map ADC to logical position
    if (adc_value < 0) {
        // ADC out-of-range error
        sim_state = SIM_IDLE;
        return;
    }
    sim_current_position = adc_value / 128; // Example: 0-1023 -> 0-7
    HAL_SetLED(sim_current_position, 1); // Indicate position
}

void SIM_ProcessCommand(int target_position) {
    sim_current_position = target_position;
    HAL_SetMotor(1);
    sim_state = SIM_UPDATING;
}

void SIM_Task(void) {
    switch(sim_state) {
    case SIM_MONITORING:
        // Monitor ADC, update
        break;
    case SIM_COMMANDED:
        // Execute command
        break;
    case SIM_UPDATING:
        // Update done, stop motor
        HAL_SetMotor(0);
        sim_state = SIM_MONITORING;
        break;
    default:
        break;
    }
}
