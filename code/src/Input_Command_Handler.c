#include "Input_Command_Handler.h"
#include <string.h>

void InputCmdHandler_Init(InputCmdHandler_t *ich) {
    ich->state = IC_IDLE;
    memset(ich->rx_buffer, 0, sizeof(ich->rx_buffer));
    ich->is_valid = 0;
}

void InputCmdHandler_Receive(InputCmdHandler_t *ich, const char *rx) {
    if (rx != NULL) {
        ich->state = IC_CMD_RX;
        strncpy(ich->rx_buffer, rx, sizeof(ich->rx_buffer)-1);
    }
}

void InputCmdHandler_Process(InputCmdHandler_t *ich) {
    ich->state = IC_VALIDATE;
    // Dummy: Accept numbers 0-5 as valid commands
    if (ich->rx_buffer[0] >= '0' && ich->rx_buffer[0] <= '5') {
        ich->is_valid = 1;
        ich->state = IC_ACCEPTED;
    } else {
        ich->is_valid = 0;
        ich->state = IC_REJECTED;
    }
}
