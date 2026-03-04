#include "PositionFeedback.h"

#define NUM_POSITIONS 5
typedef struct {
    uint16_t min_adc;
    uint16_t max_adc;
    enum FlapPosition pos;
} ADCMapEntry;

static const ADCMapEntry adcMap[NUM_POSITIONS] = {
    { 0, 409, FLAP_POS_0 },
    { 410, 819, FLAP_POS_1 },
    { 820, 1228, FLAP_POS_2 },
    { 1229, 1638, FLAP_POS_3 },
    { 1639, 2047, FLAP_POS_4 }
};

static uint16_t last_adc = 0;
static enum FlapPosition last_pos = FLAP_POS_INVALID;
static bool feedbackValid = false;

// Simulation/placeholder for actual ADC sampling
typedef uint16_t (*ADC_Read_Fn)(void);
static ADC_Read_Fn sample_adc_fn = NULL;

void PositionFeedback_Sample(void) {
    if(sample_adc_fn == NULL) {
        // ADC function needs to be set externally
        feedbackValid = false;
        last_pos = FLAP_POS_INVALID;
        return;
    }
    last_adc = sample_adc_fn();
    for(int i = 0; i < NUM_POSITIONS; ++i) {
        if(last_adc >= adcMap[i].min_adc && last_adc <= adcMap[i].max_adc) {
            last_pos = adcMap[i].pos;
            feedbackValid = true;
            return;
        }
    }
    last_pos = FLAP_POS_INVALID;
    feedbackValid = false;
}

enum FlapPosition PositionFeedback_GetPosition(void) {
    return last_pos;
}

bool PositionFeedback_IsValid(void) {
    return feedbackValid;
}

void PositionFeedback_SetAdcReadFunction(ADC_Read_Fn fn) {
    sample_adc_fn = fn;
}
