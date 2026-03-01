#include "command_handler.h"
#include "static_config.h"
static int valid_command_flag = 0;
static int command_position_idx = CMD_INVALID;
void CommandHandler_Init(void) { valid_command_flag = 0; command_position_idx = CMD_INVALID; }
void CommandHandler_UartRxHandler(uint8_t data) {
    if((data >= '0') && (data <= '5')) {
        valid_command_flag = 1;
        command_position_idx = (int)(data - (uint8_t)'0'); /* MISRA: Added explicit casts to avoid type mismatch */
    } else {
        valid_command_flag = 0;
    }
}
int CommandHandler_GetValidCommand(void) {
    if(valid_command_flag) {
        valid_command_flag = 0;
        return command_position_idx;
    }
    return CMD_INVALID;
}
