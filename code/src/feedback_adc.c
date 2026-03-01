#include "feedback_adc.h"
#include "static_config.h"
#include <stm32f4xx_hal.h>
static uint16_t adc_raw = 0U;
static uint8_t position = 0U;
static uint8_t out_of_range = 0U;
void Feedback_Init(void) { /* ADC init */ position = 0U; out_of_range = 0U; }
void Feedback_PeriodicTask(void) {
    adc_raw = 0U; /* placeholder for ADC_read(); */
    out_of_range = 1U;
    for (uint8_t i = 0U; i < 6U; ++i) {
        if ((adc_raw >= StaticConfig_GetThresholdMin(i)) && (adc_raw <= StaticConfig_GetThresholdMax(i))) {
            position = i;
            out_of_range = 0U;
            break;
        }
    }
}
uint8_t Feedback_GetPosition(void) { return position; }
uint8_t Feedback_IsValid(void) { return (uint8_t)(!out_of_range); }
