#include "feedback_processor.h"
#include <stdint.h>
// Hardware ADC stubs and constants
#define ADC_MAX 4095
static const int pos_ranges[6][2] = {
    {0, 682},    // Position 0
    {683, 1365}, // Position 1
    {1366, 2047},// Position 2
    {2048, 2730},// Position 3
    {2731, 3412},// Position 4
    {3413, 4095} // Position 5
};

static int last_position = 0;
static int last_valid = 1;

static int read_adc_raw(void) {
    // TODO: Hardware ADC driver
    return 0;
}

int FeedbackProcessor_GetPosition(int* pos_out) {
    int adc_val = read_adc_raw();
    for (int i = 0; i < 6; ++i) {
        if (adc_val >= pos_ranges[i][0] && adc_val <= pos_ranges[i][1]) {
            *pos_out = i;
            last_position = i;
            last_valid = 1;
            return 1;
        }
    }
    last_valid = 0;
    return 0;
}

int FeedbackProcessor_CheckValid(void) {
    return last_valid;
}
