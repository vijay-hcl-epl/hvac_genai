#include "pos_fb_acq.h"
#include "hal_adc.h"
#define FB_THRESHOLDS {200, 600, 1000, 1400, 1800, 2200}
static const uint16_t fb_adc_thresholds[6] = FB_THRESHOLDS;

uint8_t pos_fb_acq_get_position(void) {
    uint16_t adc = hal_adc_get_val();
    uint8_t pos; /* MISRA: Rule 17.8 – Minimize scope of variable, declare at top */
    for (pos = 0; pos < 6; ++pos) {
        if (adc < fb_adc_thresholds[pos]) { return pos; }
    }
    return 5;
}
void pos_fb_acq_init(void) { /* (could calibrate if needed) */ }
