#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

typedef enum {
    SIM_STATE_IDLE,
    SIM_STATE_SAMPLING,
    SIM_STATE_VALIDATING,
    SIM_STATE_ERROR
} SimState_t;

typedef struct {
    int adc_buffer;
    int calibration_constant;
    SimState_t state;
} SignalInterfaceManager_t;

void SIM_Init(SignalInterfaceManager_t* sim);
void SIM_SampleADC(SignalInterfaceManager_t* sim);
void SIM_ValidateADC(SignalInterfaceManager_t* sim);

#endif
