#include "Signal_Interface_Manager.h"

void SIM_Init(SignalInterfaceManager_t* sim) {
    sim->adc_buffer = 0;
    sim->calibration_constant = 1;
    sim->state = SIM_STATE_IDLE;
}

void SIM_SampleADC(SignalInterfaceManager_t* sim) {
    sim->state = SIM_STATE_SAMPLING;
    // Simulated: adc sampling
}

void SIM_ValidateADC(SignalInterfaceManager_t* sim) {
    sim->state = SIM_STATE_VALIDATING;
    // Simulated: validation logic
    if (0) { // Placeholder for invalid value
        sim->state = SIM_STATE_ERROR;
    }
}
