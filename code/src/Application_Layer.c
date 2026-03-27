#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

static ApplicationState app_state = STATE_IDLE;
static int requested_command = 0;
static int validation_status = 0;

void Application_Init(void) {
    app_state = STATE_IDLE;
    requested_command = 0;
    validation_status = 0;
}

void Application_Process(void) {
    switch (app_state) {
        case STATE_IDLE:
            requested_command = SignalInterface_ReadCommand();
            app_state = STATE_VALIDATE;
            break;
        case STATE_VALIDATE:
            // Assume command valid if in range 0-5
            validation_status = (requested_command >= 0 && requested_command <= 5);
            app_state = validation_status ? STATE_EXECUTE : STATE_ERROR;
            break;
        case STATE_EXECUTE:
            Hal_SetMotorDirection(requested_command);
            app_state = STATE_OUTPUT;
            break;
        case STATE_OUTPUT:
            Hal_SetLedState(requested_command);
            app_state = STATE_IDLE;
            break;
        case STATE_ERROR:
            Hal_SetLedState(-1);
            app_state = STATE_IDLE;
            break;
        default:
            app_state = STATE_ERROR;
            break;
    }
}
