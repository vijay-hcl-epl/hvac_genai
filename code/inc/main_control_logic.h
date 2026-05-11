#ifndef MAIN_CONTROL_LOGIC_H
#define MAIN_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

void main_control_logic_init(void);
void main_control_logic_on_cmd(uint8_t target_pos, bool valid);
void main_control_logic_on_feedback(uint8_t actual_pos, bool in_range);
void main_control_logic_on_error(void);
void main_control_logic_run(void); // main loop, call periodically

#endif // MAIN_CONTROL_LOGIC_H
