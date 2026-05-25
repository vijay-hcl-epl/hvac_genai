#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <stdbool.h>

// Flap Control API
void control_logic_init(void);
void control_logic_command(int target_position);
void control_logic_update_position(int current_position);
void control_logic_error(void);
bool control_logic_is_at_target(void);

#endif // CONTROL_LOGIC_H
