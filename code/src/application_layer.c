#include "application_layer.h"
#include "hardware_abstraction_layer.h"
#include "signal_interface_manager.h"

static uint8_t uart_rx_buffer;
static int position_command;
static AppState_t app_state = APP_IDLE;

void APP_ProcessUARTCommand(uint8_t cmd) {
    if (cmd <= 5) {
        position_command = cmd;
        app_state = APP_PROCESS_COMMAND;
    } else {
        app_state = APP_ERROR;
    }
}

void APP_Update(void) {
    switch (app_state) {
        case APP_IDLE:
            // In real app: check UART
            break;
        case APP_PROCESS_COMMAND:
            SIM_SetTargetPosition(position_command);
            app_state = APP_FEEDBACK;
            break;
        case APP_FEEDBACK:
            HAL_AllLEDOff();
            HAL_SetLED(position_command, 1);
            app_state = APP_IDLE;
            break;
        case APP_ERROR:
            // Invalid command, safe fallback
            HAL_AllLEDOff();
            app_state = APP_IDLE;
            break;
        default:
            app_state = APP_IDLE;
            break;
    }
}
