#include "feedback_processing.h"
#include "sw_config_table.h"
static uint16_t adc_raw = 0;
static uint8_t logical_position = 0;
static bool adc_invalid_flag = false;
void feedback_processing_init(void) { adc_invalid_flag = false; }
void feedback_process_adc(uint16_t adc) {
    adc_raw = adc;
    if (adc < calibration_table[0] || adc > calibration_table[position_count-1]) {
        adc_invalid_flag = true;
    } else {
        for (uint8_t i = 0; i < position_count-1; ++i) {
            if (adc >= calibration_table[i] && adc < calibration_table[i+1]) {
                logical_position = i;
                adc_invalid_flag = false;
                return;
            }
        }
    }
}
uint8_t feedback_get_position(void) { return logical_position; }
bool feedback_adc_invalid(void) { return adc_invalid_flag; }
