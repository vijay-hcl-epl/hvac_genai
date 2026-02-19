#include "fa.h"
// Stub ADC/data
static uint16_t adc_val = 0;
static const uint16_t mapping_table[6] = {100, 500, 1000, 1500, 2000, 2500};
static uint8_t last_pos = 0;
static bool oor_flag = false;
void fa_init(void) {
    adc_val = 0;
    last_pos = 0;
    oor_flag = false;
}
void fa_update(void) {
    // emulated ADC
}
bool fa_is_oor(void) {
    // Logic: if ADC not in mapped window
    return oor_flag;
}
uint8_t fa_get_pos(void) {
    uint16_t val = adc_val;
    for (uint8_t n = 0; n < 6; ++n) {
        if (val < mapping_table[n]) {
            last_pos = n;
            oor_flag = false;
            return n;
        }
    }
    oor_flag = true;
    return last_pos;
}
