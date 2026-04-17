#include "adc_interface.h"
#define ADC_MIN_VAL 100
#define ADC_MAX_VAL 4000
#define ADC_POS_STEP 700 // Example mapping
static uint16_t last_adc = 0;
static uint8_t last_logical = 0;
static bool valid = false;
void adc_interface_init(void) { last_adc = 0; last_logical = 0; valid = false; }
uint8_t adc_interface_get_position(void)
{
    // Simulated ADC read -- Replace with MCU ADC code
    uint16_t sample = last_adc; // Here, add ADC HW reading
    if (sample < ADC_MIN_VAL || sample > ADC_MAX_VAL) { valid = false; return 0; }
    valid = true;
    last_logical = (sample - ADC_MIN_VAL) / ADC_POS_STEP;
    if (last_logical > 5) last_logical = 5;
    return last_logical;
}
bool adc_interface_is_valid(void) { return valid; }
