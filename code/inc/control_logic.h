#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <stdint.h>

void control_logic_init(void);
void control_logic_move_to_position(uint8_t target_pos);
void control_logic_periodic(void);

#endif // CONTROL_LOGIC_H
