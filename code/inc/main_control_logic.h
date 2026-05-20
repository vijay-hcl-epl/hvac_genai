#ifndef MAIN_CONTROL_LOGIC_H
#define MAIN_CONTROL_LOGIC_H

void main_control_process_command(int target_position);
void main_control_update_feedback(int actual_position);
void main_control_handle_error(void);

#endif
