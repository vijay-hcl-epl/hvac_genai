#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"

static app_state_t app_state = APP_IDLE;
static int last_valid_cmd = -1;

void APP_Init(void) {
    app_state = APP_IDLE;
}

void APP_Task(void) {
    switch(app_state) {
        case APP_IDLE:
            // Wait for UART transfer via Signal_Interface_Manager
            break;
        case APP_CMD_RECEIVED:
            // Validate command buffer, set move sequence
            app_state = APP_MOVE_FLAP;
            break;
        case APP_MOVE_FLAP:
            // Issue position command toward Hardware Abstraction Layer
            app_state = APP_FLAP_IN_POSITION;
            break;
        case APP_FLAP_IN_POSITION:
            // Confirm in position, reset
            app_state = APP_IDLE;
            break;
    }
}

void APP_ReceivePosition(uint16_t adc_value) {
    // Used by Signal_Interface_Manager to deliver decoded position
    last_valid_cmd = adc_value;
}
