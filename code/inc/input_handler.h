#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdint.h>

// User command types
#define FLAP_CMD_MIN 0
#define FLAP_CMD_MAX 100

typedef enum {
    USER_CMD_NONE = 0,
    USER_CMD_POSITION,
    USER_CMD_ERROR
} user_cmd_type_t;

extern volatile user_cmd_type_t user_command;
extern volatile uint8_t valid_command_flag;
extern volatile uint8_t error_state_flag;

user_cmd_type_t GetUserCommand(int* out_position);
void TriggerSafeState(void);

#endif // INPUT_HANDLER_H
