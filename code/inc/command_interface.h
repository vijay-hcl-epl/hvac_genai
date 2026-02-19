#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    CMD_TYPE_NONE = 0,
    CMD_TYPE_POSITION
} command_type_t;

typedef struct {
    command_type_t type;
    uint16_t target_position;
    bool valid_command_flag;
} command_t;

void command_interface_init(void);
void command_interface_receive_byte(uint8_t byte);
command_t command_interface_get_valid_command(void);
void command_interface_clear_flag(void);

#endif // COMMAND_INTERFACE_H
