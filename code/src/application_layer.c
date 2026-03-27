#include "application_layer.h"
#include "signal_interface_manager.h"

static ApplicationState_t appState = APP_IDLE;
static AppCommandContext_t cmdContext;

void ApplicationLayer_Init(void) {
    appState = APP_IDLE;
    cmdContext.command = 0;
    cmdContext.valid = 0;
}

void ApplicationLayer_ExecCycle(void) {
    switch (appState) {
        case APP_IDLE:
            // Stub to get command from UART interface
            cmdContext.valid = 0; // Should be set when new UART data present
            // TODO: Replace with UART rx logic
            break;
        case APP_PARSE_CMD:
            // Command validation
            if (cmdContext.valid) {
                appState = APP_EXECUTE_ACTION;
            } else {
                appState = APP_IDLE;
            }
            break;
        case APP_EXECUTE_ACTION:
            // Delegate to signal interface
            if (cmdContext.valid) {
                SignalInterfaceManager_HandleCommand(cmdContext.command);
            }
            appState = APP_ACK;
            break;
        case APP_ACK:
            // TODO: Send Ack/Nack to UART
            appState = APP_IDLE;
            break;
    }
}
