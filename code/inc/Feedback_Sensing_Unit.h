#ifndef FEEDBACK_SENSING_UNIT_H
#define FEEDBACK_SENSING_UNIT_H

#include <stdint.h>

// Structs from Internal Data Design
typedef struct {
    uint16_t adc_raw;
    uint8_t mapped_position;
    uint16_t adc_min;
    uint16_t adc_max;
    uint8_t adc_err;
    uint8_t median_window[3];
    uint8_t median_index;
    uint8_t error_out_of_range;
} FeedbackSensingUnitData;

// Enums from State Machine
typedef enum {
    FSU_SAMPLE_ADC = 0,
    FSU_MAP_POSITION,
    FSU_CHECK_ADC_RANGE,
    FSU_REPORT_STATUS
} FeedbackSensingUnitState;

// Function declaration for each responsibility
void Feedback_Sensing_Unit_resp_1(FeedbackSensingUnitData* data);
void Feedback_Sensing_Unit_resp_2(FeedbackSensingUnitData* data);
void Feedback_Sensing_Unit_resp_3(FeedbackSensingUnitData* data);

#endif // FEEDBACK_SENSING_UNIT_H
