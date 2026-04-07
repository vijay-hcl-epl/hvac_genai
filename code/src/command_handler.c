#include "command_handler.h"
#include "position_manager.h"
#include "uart_drv.h"
static volatile uint8_t uart_rx_buf = 0;
static volatile uint8_t command_in_progress = 0;
static uint8_t invalid_cmd_count = 0;
// UART RX ISR or poll calls this
CmdStatus_t validate_and_dispatch(uint8_t cmd) {
    if (command_in_progress) return CMD_BUSY;
    if ((cmd < 0) || (cmd > 5)) {
        invalid_cmd_count++;
        return CMD_IGNORED;
    }
    command_in_progress = 1;
    if (PositionManager_command(cmd) == POSMGR_ACCEPTED) {
        command_in_progress = 0;
        return CMD_ACCEPTED;
    } else {
        command_in_progress = 0;
        return CMD_BUSY;
    }
}
void command_handler_init(void) {
    uart_rx_buf = 0;
    command_in_progress = 0;
    invalid_cmd_count = 0;
}
