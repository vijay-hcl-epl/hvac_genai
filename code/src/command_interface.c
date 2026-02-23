#include "command_interface.h"
#include "control_logic.h"
#define UART_BUFFER_SIZE 8
static uint8_t uart_buffer[UART_BUFFER_SIZE];
static uint8_t uart_buffer_idx = 0;
static uint8_t command_in_progress = 0;
static uint8_t last_command = 0xFF;
CmdStatus_t SendFlapCmdRequest(uint8_t position) {
    if (command_in_progress) return CMD_BUSY;
    if (position > 5) return CMD_INVALID;
    command_in_progress = 1;
    last_command = position;
    ControlLogic_OnCommand(position);
    return CMD_OK;
}
void CommandInterface_UartRxHandler(uint8_t data) {
    if (uart_buffer_idx < UART_BUFFER_SIZE) {
        uart_buffer[uart_buffer_idx++] = data;
        if (data == '\n') {
            uint8_t val = 0xFF;
            // Minimal convert: expect '0'-'5' as ASCII
            if (uart_buffer[0] >= '0' && uart_buffer[0] <= '5')
                val = uart_buffer[0] - '0';
            CmdStatus_t s = SendFlapCmdRequest(val);
            // Clear buffer on any outcome
            uart_buffer_idx = 0;
        }
    } else {
        uart_buffer_idx = 0;
    }
}
void CommandInterface_Init(void) {
    uart_buffer_idx = 0;
    command_in_progress = 0;
    last_command = 0xFF;
}
// Called when command done
void CommandInterface_CommandComplete(void) {
    command_in_progress = 0;
    uart_buffer_idx = 0;
}
