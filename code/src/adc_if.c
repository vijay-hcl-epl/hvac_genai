#include "adc_if.h"
#include "configuration.h"
#include "error_handler.h"
static uint16_t adc_last_value = 0;
void AdcIf_Init(void) {
    // Hardware ADC init placeholder
    adc_last_value = 0;
}
uint16_t AdcIf_ReadRaw(void) {
    // Dummy hardware read
    adc_last_value = 1234;
    return adc_last_value;
}
uint8_t AdcIf_GetPosition(void) {
    adc_last_value = AdcIf_ReadRaw();
    // Use calibration thresholds from configuration
    uint8_t i;
    const uint16_t *thresh = Configuration_GetThresholds();
    for (i = 0; i < 5; i++) {
        if (adc_last_value < thresh[i]) return i;
    }
    return 5;
}
