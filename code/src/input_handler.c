#include "input_handler.h"
#include <string.h>

static uint8_t command_buffer[CMD_BUF_SIZE];
static uint8_t buffer_pos = 0;
static int8_t parsed_cmd = -1;
static bool cmd_pending = false;
static UART_Status_t uart_rx_status = UART_NO_CMD;

void InputHandler_Init(void)
{
    buffer_pos = 0;
    parsed_cmd = -1;
    cmd_pending = false;
    uart_rx_status = UART_NO_CMD;
    memset(command_buffer, 0, sizeof(command_buffer));
}

void InputHandler_UART_RxHandler(uint8_t rx_byte)
{
    if (cmd_pending) { return; } // Only one command at a time
    if (rx_byte >= '0' && rx_byte <= '5') {
        parsed_cmd = rx_byte - '0';
        cmd_pending = true;
        uart_rx_status = UART_OK;
        buffer_pos = 0;
        memset(command_buffer, 0, sizeof(command_buffer));
    } else {
        // Ignore invalid command, do not flag command
        parsed_cmd = -1;
        cmd_pending = false;
        uart_rx_status = UART_ERR_RANGE;
        buffer_pos = 0;
        memset(command_buffer, 0, sizeof(command_buffer));
    }
}

bool InputHandler_CommandPending(void)
{
    return cmd_pending;
}

int8_t InputHandler_GetPendingCommand(void)
{
    if (cmd_pending) {
        return parsed_cmd;
    } else {
        return -1;
    }
}

void InputHandler_ClearPending(void)
{
    cmd_pending = false;
    parsed_cmd = -1;
}

UART_Status_t InputHandler_GetStatus(void)
{
    return uart_rx_status;
}
