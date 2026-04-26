#ifndef POSITION_SENSING_FEEDBACK_H
#define POSITION_SENSING_FEEDBACK_H

#include <stdint.h>

void position_sensing_init(void);
void update_position_feedback(void);
unsigned int get_current_logical_position(void);
bool adc_in_bounds(unsigned int adc_val);
uint16_t get_adc_sample(void);

#endif // POSITION_SENSING_FEEDBACK_H
