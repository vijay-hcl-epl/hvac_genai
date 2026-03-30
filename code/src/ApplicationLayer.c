#include "ApplicationLayer.h"
#include "SignalInterfaceManager.h"

void AppLayer_Init(ApplicationLayer_t* instance) {
    instance->state = WAIT_FOR_COMMAND;
    instance->cmd_valid = 0;
    instance->target_position = 0;
    // clear uart_cmd_buffer
    for(int i = 0; i < 16; ++i) instance->uart_cmd_buffer[i] = 0;
}

void AppLayer_Run(ApplicationLayer_t* instance) {
    switch(instance->state) {
        case WAIT_FOR_COMMAND:
            // Poll or get UART input (abstract)
            // simulate_uart_receive(instance->uart_cmd_buffer, &instance->cmd_valid);
            if(instance->cmd_valid) {
                instance->state = VALIDATE_COMMAND;
            }
            break;
        case VALIDATE_COMMAND:
            // Assume simple numeric command, e.g., ASCII to int
            if(instance->uart_cmd_buffer[0] >= '0' && instance->uart_cmd_buffer[0] <= '9') {
                instance->target_position = instance->uart_cmd_buffer[0] - '0';
                instance->state = ISSUE_TO_SIGNAL_MANAGER;
            } else {
                // Invalid input, discard
                instance->cmd_valid = 0;
                instance->state = IDLE;
            }
            break;
        case ISSUE_TO_SIGNAL_MANAGER:
            // Pass to Signal Manager (abstract)
            // SignalInterfaceManager_ReceiveCommand(instance->target_position);
            instance->cmd_valid = 0; // Consumed
            instance->state = IDLE;
            break;
        case IDLE:
            // Remain idle until next input
            instance->state = WAIT_FOR_COMMAND;
            break;
        default:
            instance->state = WAIT_FOR_COMMAND;
            break;
    }
}
