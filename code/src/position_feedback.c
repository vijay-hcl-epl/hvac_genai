#include "position_feedback.h"
#include "config_data_store.h"

static int last_adc = 0;
static int last_position = -1;
static bool valid = false;

void PositionFeedback_Init(void) {
    last_adc = 0;
    last_position = -1;
    valid = false;
}

void PositionFeedback_Sample(void) {
    int adc = Config_ADC_ReadRaw();
    last_adc = adc;
    valid = false;
    for (int i = 0; i < ConfigDataStore_GetPositionCount(); i++) {
        if (adc >= ConfigDataStore_GetADCMin(i) && adc <= ConfigDataStore_GetADCMax(i)) {
            last_position = i;
            valid = true;
            return;
        }
    }
    last_position = -1;
}

int PositionFeedback_GetPosition(void) {
    return last_position;
}

bool PositionFeedback_IsValid(void) {
    return valid;
}

bool PositionFeedback_IsPositionValid(int position) {
    // Valid if position integer is defined in configuration
    return (position >= 0 && position < ConfigDataStore_GetPositionCount());
}
