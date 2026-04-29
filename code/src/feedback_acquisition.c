#include "feedback_acquisition.h"
#include <stdint.h>
#include <stdbool.h>
// ADC value ranges for each flap position
#define N_POSITIONS 6
static const struct { uint16_t start; uint16_t end; } adc_position_table[N_POSITIONS] = {
    {0U, 682U},   // 0 - Fully Closed
    {683U, 1365U},// 1
    {1366U, 2047U},// 2
    {2048U, 2730U},// 3
    {2731U, 3412U},// 4
    {3413U, 4095U}// 5 - Fully Open
};

static uint16_t read_adc_raw(void) {
    // Replace with HAL_ADC_Poll or DMA reading function
    return 0U; // Dummy value
}

int feedback_acquire(uint8_t* pos_out, bool* valid_out) {
    uint16_t value = read_adc_raw();
    for (uint8_t i = 0; i < N_POSITIONS; ++i) {
        if (value >= adc_position_table[i].start && value <= adc_position_table[i].end) {
            *pos_out = i;
            *valid_out = true;
            return 0;
        }
    }
    *valid_out = false;
    return 1;
}
