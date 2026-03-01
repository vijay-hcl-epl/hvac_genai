#ifndef FEEDBACK_PROCESSING_H
#define FEEDBACK_PROCESSING_H
#include <stdint.h>
#include <stdbool.h>
void feedback_processing_init(void);
void feedback_process_adc(uint16_t adc_raw);
uint8_t feedback_get_position(void);
bool feedback_adc_invalid(void);
#endif // FEEDBACK_PROCESSING_H
