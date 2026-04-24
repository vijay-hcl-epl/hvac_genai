#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdbool.h>

void flap_control_init(void);
void flap_control_start_move(int target_pos);
void flap_control_stop(void);
bool flap_control_is_safe(void);
bool flap_control_is_at_target(void);
bool flap_control_is_fault(void);

#endif // FLAP_CONTROL_LOGIC_H
