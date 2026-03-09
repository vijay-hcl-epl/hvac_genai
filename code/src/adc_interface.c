#include "adc_interface.h"
#include "error_handler.h"

static uint16_t adc_last_value = 0;

void ADC_Interface_Init(void) {
    adc_last_value = 0;
}

uint8_t ADC_Interface_GetPosition(void) {
    // scale 0-4095 ADC to 0-5 position (stub linear scale)
    uint16_t raw = ADC_Interface_GetRaw();
    if (raw > 4095) {
        ErrorHandler_SetError(0x10); // Range error
        return 0xFF;
    }
    return (uint8_t)((raw * 6) / 4096);
}

uint16_t ADC_Interface_GetRaw(void) {
    // return stub ADC value in [0,4095]
    // In real firmware, would read from hardware
    return adc_last_value;
}
