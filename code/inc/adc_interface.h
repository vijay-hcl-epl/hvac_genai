#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>
void adc_interface_init(void);
// Samples ADC and maps to logical 0-5 position
uint8_t adc_interface_get_position(void);
// Returns true if latest ADC sample in valid range
bool adc_interface_is_valid(void);
#endif
