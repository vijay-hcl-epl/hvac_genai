#include "adc_interface.h"
#include "config_data.h"
#include "error_handler.h"

static uint16_t adc_last_value = 0;

void ADCInterface_Init(void) {
    adc_last_value = 0;
}

void ADCInterface_StartConversion(void) {
    // Hardware specific: trigger ADC, poll for result
    adc_last_value = 1030; // dummy placeholder (should read real ADC)
}

uint16_t ADCInterface_GetLastValue(void) {
    return adc_last_value;
}

uint8_t ADCInterface_GetPosition(void) {
    // Map ADC value to flap position (0–5) using thresholds
    const ConfigData_t* cfg = ConfigData_Get();
    for(uint8_t i=0; i<6; ++i) {
        if(adc_last_value <= cfg->adc_thresholds[i]) {
            return i;
        }
    }
    // If not within thresholds, out-of-range
    ErrorHandler_Set(ERR_ADC_OOR);
    return 0xFF;
}
