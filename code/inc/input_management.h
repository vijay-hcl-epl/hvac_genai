#ifndef INPUT_MANAGEMENT_H
#define INPUT_MANAGEMENT_H

#include <stdbool.h>

void input_mgmt_init(void);
bool process_uart_rx(const char *buffer, unsigned int len);
void send_command_to_control(unsigned int requested_position);

#endif // INPUT_MANAGEMENT_H
