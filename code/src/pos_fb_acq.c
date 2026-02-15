#include "pos_fb_acq.h"
#include "hal_adc.h"
#define FB_THRESHOLDS {200U, 600U, 1000U, 1400U, 1800U, 2200U}
static const uint16_t fb_adc_thresholds[6] = FB_THRESHOLDS;

uint8_t pos_fb_acq_get_position(void)
{
    uint16_t adc = hal_adc_get_val();
    uint8_t pos;
    for (pos = 0U; pos < 6U; ++pos) {
        if (adc < fb_adc_thresholds[pos]) {
            return pos;
        }
    }
    return 5U;
}
void pos_fb_acq_init(void)
{
    /* (could calibrate if needed) */
}
