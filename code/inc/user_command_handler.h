#ifndef USER_COMMAND_HANDLER_H
#define USER_COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_LEN_MAX 16

typedef enum {
    CMD_INVALID = 0,
    CMD_VALID = 1
} CmdStatus_t;

typedef struct {
    char buffer[CMD_LEN_MAX];
    uint8_t len;
} UartCmdBuffer_t;

void user_command_handler_init(void);
CmdStatus_t parse_user_command(const char *uart_data, uint16_t *parsed_position);
uint8_t user_command_handler_get_error_count(void);

#endif // USER_COMMAND_HANDLER_H
