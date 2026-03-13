#include "user_command_if.h"
#include "error_handler.h"
#include <string.h>

static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t cmd_value = CMD_POS_MIN;
static uint8_t status_code = UART_OK;
static uint8_t cmd_ready = 0;
static uint8_t error_count = 0;

void UserCommandIF_Init(void) {
    memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
    cmd_value = CMD_POS_MIN;
    status_code = UART_OK;
    cmd_ready = 0;
    error_count = 0;
}

void UserCommandIF_RxISR(uint8_t byte) {
    if (byte >= '0' && byte <= '5') {
        cmd_value = (uint8_t)(byte - '0');
        status_code = UART_OK;
        cmd_ready = 1;
    } else {
        error_count++;
        status_code = UART_ERR;
        ErrorHandler_Set(ERR_CMD_INVALID);
        cmd_ready = 0;
    }
}

void UserCommandIF_Process(void) {
    // Called in main loop to move new command to target
    // No action if cmd_ready = 0
}

uint8_t UserCommandIF_GetCmd(void) {
    if(cmd_ready) {
        cmd_ready = 0;
        return cmd_value;
    }
    return 0xFF;
}

uint8_t UserCommandIF_GetStatus(void) {
    return status_code;
}
