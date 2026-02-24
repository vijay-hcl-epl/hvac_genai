/* PositionFeedbackProcessor.c - Implements Position Feedback Processor unit */
#include "PositionFeedbackProcessor.h"
#include "ConfigStateManager.h"

// Simulated ADC hardware read (to be replaced per platform)
static uint16_t adc_read(void) {
    // Platform/MCU-specific ADC acquisition
    // Dummy return for compile (replace with real hardware API)
    return 0;
}
// Static configuration
static const uint16_t adcThresholds[NUM_FLAP_POSITIONS+1] = { 200, 600, 1000, 1400, 1800, 2200, 4096 };
static volatile uint16_t lastADCVal = 0;
static volatile int8_t logicalPos = FLAP_POS_INVALID;
static volatile bool outOfRangeFlag = false;

void PosFb_Processor_Init(void) {
    lastADCVal = 0;
    logicalPos = FLAP_POS_INVALID;
    outOfRangeFlag = false;
}

void PosFb_Processor_TriggerSample(void) {
    lastADCVal = adc_read();
    outOfRangeFlag = true;
    logicalPos = FLAP_POS_INVALID;
    for (uint8_t i = 0; i < NUM_FLAP_POSITIONS; i++) {
        if (lastADCVal < adcThresholds[i+1]) {
            logicalPos = i;
            outOfRangeFlag = false;
            break;
        }
    }
}

int8_t PosFb_Processor_GetPosition(void) {
    return logicalPos;
}

bool PosFb_Processor_IsOutOfRange(void) {
    return outOfRangeFlag;
}
