#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <stdbool.h>

void control_logic_init(void);
void control_logic_execute_cycle(void);
bool control_logic_is_moving(void);
bool control_logic_get_error(void);
void control_logic_command_complete(void);

#endif // CONTROL_LOGIC_H
