#ifndef HAL_ADC_H
#define HAL_ADC_H
#include <stdint.h>
void hal_adc_init(void);
uint16_t hal_adc_get_val(void);
#endif // HAL_ADC_H
