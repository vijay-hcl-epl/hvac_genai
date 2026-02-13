#include "cmd_proc.h"
#include "uart_cmd_if.h"
#include "flap_pos_ctrl.h"
static enum { IDLE, IN_PROGRESS } cmd_proc_state = IDLE;
static uint8_t current_cmd = 0xFF;

void cmd_proc_init(void) { cmd_proc_state = IDLE; current_cmd = 0xFF; }
void cmd_proc_next(void) {
    if (cmd_proc_state == IN_PROGRESS) { /* MISRA: Rule 14.9 – If-else statement must use braces */  return; }
    if (uart_cmd_if_parsed_cmd_available()) {
        uint8_t cmd = uart_cmd_if_get_command();
        if (cmd <= 5) {
            flap_pos_ctrl_set_target(cmd);
            current_cmd = cmd;
            cmd_proc_state = IN_PROGRESS;
        }
    }
    if (flap_pos_ctrl_movement_complete()) {
        cmd_proc_state = IDLE;
    }
}
