#include "position_feedback.h"
#include "calibration_data.h"
#include "error_handler.h"
#define FEEDBACK_HISTORY 4
static uint16_t adc_history[FEEDBACK_HISTORY];
static uint8_t idx = 0;
static uint8_t last_position = 0;
void PositionFeedback_Init(void) {
    for (int i = 0; i < FEEDBACK_HISTORY; ++i) adc_history[i] = 0;
    idx = 0;
    last_position = 0;
}
void PositionFeedback_AdcInterruptHandler(uint16_t adc_value) {
    if (adc_value == 0xFFFF || adc_value < 50 || adc_value > 4000) {
        ErrorHandler_SetErrorState(1);
        return;
    }
    adc_history[idx++] = adc_value;
    if (idx >= FEEDBACK_HISTORY) idx = 0;
    uint8_t pos = MapAdcToPosition(adc_value);
    if (pos == 0xFF) {
        ErrorHandler_SetErrorState(2);
        return;
    }
    last_position = pos;
}
uint8_t GetCurrentFlapPosition(void) { return last_position; }
