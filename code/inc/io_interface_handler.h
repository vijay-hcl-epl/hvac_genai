#ifndef IO_INTERFACE_HANDLER_H
#define IO_INTERFACE_HANDLER_H

#include <stdint.h>

#define ADC_INVALID_VALUE 0xFFFF

uint16_t read_adc_value(void);
void signal_event(void);

#endif // IO_INTERFACE_HANDLER_H
