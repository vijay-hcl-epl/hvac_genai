#ifndef MAIN_CONTROL_H
#define MAIN_CONTROL_H

void main_control_init(void);
void main_control_process_command(int position);
void main_control_update_position(int actual_position);
void main_control_handle_error(void);

#endif
