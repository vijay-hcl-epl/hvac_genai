#include "adc_feedback.h"
static uint16_t adc_raw = 0;
static uint8_t position = 0;
static bool error_flag = false;
void ADCFbk_Init(void) {
    error_flag = false;
    position = 0;
    adc_raw = 0;
}
void ADCFbk_GetPosition(uint8_t *value, bool *error) {
    adc_raw = 2000; // Simulated ADC sample
    if (adc_raw > 4095) {
        error_flag = true;
        position = 0;
    } else {
        error_flag = false;
        position = adc_raw / 700; // Example scale for 0-5
    }
    if (value) *value = position;
    if (error) *error = error_flag;
}
