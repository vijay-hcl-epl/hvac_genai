#include "application_layer.h"
#include "signal_interface_manager.h"
#include "hw_abstraction_layer.h"

static ApplicationLayerData_t appData;

void ApplicationLayer_Init(void) {
    appData.uart_cmd = 0;
    appData.current_flap_position = 0;
    appData.system_state = 0;
}

void ApplicationLayer_Run(void) {
    static AppState_t state = APP_WAITING_FOR_CMD;
    switch(state) {
        case APP_WAITING_FOR_CMD:
            // Wait for UART command
            // simplified: suppose new command detected
            state = APP_PROCESS_CMD;
            break;
        case APP_PROCESS_CMD:
            // Validate UART command
            // Call Signal Interface Manager
            state = APP_UPDATE_STATE;
            break;
        case APP_UPDATE_STATE:
            // Update system state
            state = APP_WAITING_FOR_CMD;
            break;
        default:
            // Error recovery
            state = APP_WAITING_FOR_CMD;
            break;
    }
}
