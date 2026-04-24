#include "sensing.h"
#include "hardware_abstraction.h"
#include <stdint.h>

#define FLAP_POS_MIN_ADC 0
#define FLAP_POS_MAX_ADC 4095
#define ADC_THRESHOLDS {0, 682, 1364, 2046, 2728, 3410, 4095}
static const int adc_bounds[7] = ADC_THRESHOLDS;
#define LOGICAL_POS_COUNT 6

static int latest_pos = -1;
static bool valid = false;

void SENS_Init(void) {
    latest_pos = -1;
    valid = false;
}

bool SENS_GetCurrentPosition(int *out_position) {
    if (!valid || out_position == NULL) return false;
    *out_position = latest_pos;
    return true;
}

void SENS_PeriodicSample(void) {
    int adc_val = HA_SampleADC();
    valid = false;
    for (int i = 0; i < LOGICAL_POS_COUNT; ++i) {
        if (adc_val >= adc_bounds[i] && adc_val <= adc_bounds[i + 1]) {
            latest_pos = i;
            valid = true;
            break;
        }
    }
}
