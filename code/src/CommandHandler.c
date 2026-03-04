/* CommandHandler.c - Implementation for command receive and validation */
#include "CommandHandler.h"
#include "UART.h"

static uint8_t lastReceivedCmd = CMD_FLAP_POS_MIN;

void CommandHandler_Init(void) {
    lastReceivedCmd = CMD_FLAP_POS_MIN;
}

bool CommandHandler_ReceiveCommand(uint8_t* targetPos) {
    uint8_t cmd = 0;
    if (UART_Read(&cmd)) {
        return CommandHandler_Validate(cmd, targetPos);
    }
    return false;
}

bool CommandHandler_Validate(uint8_t cmd, uint8_t* validCmd) {
    if (cmd >= CMD_FLAP_POS_MIN && cmd <= CMD_FLAP_POS_MAX) {
        *validCmd = cmd;
        lastReceivedCmd = cmd;
        return true;
    }
    return false;
}
