#include "feedback_sensing_unit.h"

// Responsibility: Monitor and provide current flap position using potentiometer ADC values.
void feedback_sensing_unit_resp_0(FeedbackSensingUnitData* data) {
    FeedbackSensingUnitState state = STATE_MONITOR_POSITION;
    switch(state) {
        case STATE_MONITOR_POSITION:
            // Algorithm steps from LLD
            // 1. Read ADC value (stub: simulate read)
            data->adc_value = 0; // Deterministic stub (replace with actual read)

            // 2. Map ADC value to logical position (stub: simulate logic)
            if (data->adc_value < 0 || data->adc_value > 1023) {
                // Error Handling: Invalid ADC value (out of range)
                data->logical_position_index = -1;
            } else {
                data->logical_position_index = (data->adc_value / 128); // Example mapping per design
            }

            // 3. Store current position (already in struct)
            break;
        default:
            // No other states
            break;
    }
}
