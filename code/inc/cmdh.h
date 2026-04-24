#ifndef CMDH_H
#define CMDH_H

#include <stdbool.h>
#include <stdint.h>

#define CMDH_CMD_INVALID   (-1)
#define CMDH_CMD_MIN      (0)
#define CMDH_CMD_MAX      (5)

void cmdh_init(void);
void cmdh_uart_rx_callback(const char *data, uint32_t len);
bool cmdh_get_last_valid_command(int *cmd_value);

#endif // CMDH_H
