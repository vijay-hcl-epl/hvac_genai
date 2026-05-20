#include "uart_command_handler.h"
#include "main_control_logic.h"
#include <stdlib.h>

void uart_command_receive(const char *cmd) {
    int pos = atoi(cmd);
    if (pos >= 0) {
        main_control_process_command(pos);
    }
}
