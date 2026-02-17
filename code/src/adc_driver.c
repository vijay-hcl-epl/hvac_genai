#include "adc_driver.h"
// [TBD — Not in source]: Register macros, ISR, ADC result val
static ADC_Config g_adc_cfg;
void ADC_init(const ADC_Config* config) { g_adc_cfg = *config; /* [TBD — HW setup] */ }
uint8_t ADC_start(uint8_t channel) { return 0; /* [TBD — HW start] */ }
uint16_t ADC_result(void) { return 0; /* [TBD — HW result] */ }
uint8_t ADC_status(void) { return 0; /* [TBD — HW status] */ }
