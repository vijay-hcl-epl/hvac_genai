#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

void Application_Init(void) {
    app_state = STATE_IDLE;
    app_requested_command = 0;
    app_validation_status = 0;
    app_output_request_state = 0;
}

void Application_Process(void) {
    switch (app_state) {
        case STATE_IDLE:
            app_requested_command = SignalInterface_ReadCommand();
            app_state = STATE_VALIDATE;
            break;
        case STATE_VALIDATE:
            if (app_requested_command >= 0) {
                app_validation_status = 1;
                app_state = STATE_EXECUTE;
            } else {
                app_state = STATE_ERROR;
            }
            break;
        case STATE_EXECUTE:
            Hal_SetMotorDirection(app_requested_command);
            app_state = STATE_OUTPUT;
            break;
        case STATE_OUTPUT:
            Hal_SetLedState(0, 1); // Example status LED
            app_state = STATE_IDLE;
            break;
        case STATE_ERROR:
            Hal_StopMotor();
            Hal_SetLedState(1, 1); // Error indicator
            app_state = STATE_IDLE;
            break;
        default:
            app_state = STATE_ERROR;
            break;
    }
}
