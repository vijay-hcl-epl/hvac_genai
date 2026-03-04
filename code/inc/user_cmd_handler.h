#ifndef USER_CMD_HANDLER_H
#define USER_CMD_HANDLER_H
#include <stdint.h>
#include <stdbool.h>

void user_cmd_handler_init(void);
void user_cmd_handler_receive(uint8_t data);
bool is_cmd_valid(void);
uint8_t get_last_cmd_position(void);

#endif // USER_CMD_HANDLER_H
