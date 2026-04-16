#ifndef FLAPPOSITIONCONTROLUNIT_H
#define FLAPPOSITIONCONTROLUNIT_H

typedef enum {
    MoveToPosition,
    AtTarget,
    PositionMapping,
    Fault
} FlapPositionControlState;

typedef struct {
    int target_position; // 1–6
    int motor_status; // ON/OFF
    int position_bin[6];
    int adc_fault_flag;
} FlapPositionControlVars;

void FlapPositionControlUnit_resp_1();
void FlapPositionControlUnit_resp_2();
void FlapPositionControlUnit_resp_3();
void FlapPositionControlUnit_resp_4();

#endif
