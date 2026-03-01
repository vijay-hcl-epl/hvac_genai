#include "feedback_adc.h"
#include "static_config.h"
#include <stm32f4xx_hal.h>
static uint16_t adc_raw = 0;
static uint8_t position = 0;
static uint8_t out_of_range = 0;
void Feedback_Init(void) { /* ADC init */ position = 0; out_of_range = 0; }
void Feedback_PeriodicTask(void) {
    adc_raw = 0; // placeholder for ADC_read();
    out_of_range = 1u;
    for (uint8_t i = 0; i < 6; ++i) {
        if ((adc_raw >= StaticConfig_GetThresholdMin(i)) && (adc_raw <= StaticConfig_GetThresholdMax(i))) {
            position = i;
            out_of_range = 0u;
            break;
        }
    }
}
uint8_t Feedback_GetPosition(void) { return position; }
uint8_t Feedback_IsValid(void) { return !out_of_range; }
