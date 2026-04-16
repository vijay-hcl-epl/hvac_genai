#ifndef FEEDBACK_SENSING_UNIT_H
#define FEEDBACK_SENSING_UNIT_H

#include <stdint.h>

// Internal Data Design
typedef struct {
    int adc_value;
    int logical_position_index;
} FeedbackSensingUnitData;

// State Machine
typedef enum {
    STATE_MONITOR_POSITION
} FeedbackSensingUnitState;

// Function Declarations
void feedback_sensing_unit_resp_0(FeedbackSensingUnitData* data);

#endif // FEEDBACK_SENSING_UNIT_H
