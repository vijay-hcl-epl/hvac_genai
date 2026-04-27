#ifndef MAIN_CONTROL_LOGIC_H
#define MAIN_CONTROL_LOGIC_H
#include <stdint.h>

void main_control_logic_init(void);
void main_control_logic_periodic(void);
void main_control_logic_on_position_cmd(uint8_t logical_position);
void main_control_logic_on_position_feedback(uint8_t logical_position, int adc_val, bool in_range);
void main_control_logic_on_error(void);

#endif // MAIN_CONTROL_LOGIC_H
