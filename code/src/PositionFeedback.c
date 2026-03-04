#include "PositionFeedback.h"
#include "ADC.h"
#include "ErrorHandler.h"
static uint16_t last_adc = 0;
static uint8_t logical_position = 0;
void PositionFeedback_Init(void) {
    last_adc = 0;
    logical_position = 0;
}
void PositionFeedback_Process(void) {
    last_adc = ADC_GetValue();
    if (last_adc < 600) logical_position = 0;
    else if (last_adc < 1200) logical_position = 1;
    else if (last_adc < 1800) logical_position = 2;
    else if (last_adc < 2400) logical_position = 3;
    else if (last_adc < 3000) logical_position = 4;
    else if (last_adc <= 4095) logical_position = 5;
    else ErrorHandler_Report(11); // Out of range
}
uint8_t PositionFeedback_GetPosition(void) {
    return logical_position;
}
