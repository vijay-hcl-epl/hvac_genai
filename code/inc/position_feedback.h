#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t min_adc;
    uint16_t max_adc;
    uint16_t thresholds[6];
} PositionCalibration_t;

void PositionFeedback_Init(const PositionCalibration_t* calib);
void PositionFeedback_ADC_Update(uint16_t adc_value);
uint8_t PositionFeedback_GetLogicalPosition(void);
bool PositionFeedback_IsValid(void);

#endif // POSITION_FEEDBACK_H
