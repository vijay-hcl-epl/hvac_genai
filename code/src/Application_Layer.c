#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

static ApplicationLayer_Data_t appData;

void Application_Init(void) {
    appData.requestedCommand = APP_CMD_NONE;
    appData.currentState = APP_STATE_IDLE;
    appData.isValid = 0;
    appData.outputRequest = 0;
}

void Application_Process(void) {
    switch (appData.currentState) {
        case APP_STATE_IDLE:
            appData.requestedCommand = SignalInterface_ReadCommand();
            if (appData.requestedCommand != APP_CMD_INVALID) {
                appData.currentState = APP_STATE_VALIDATE;
            }
            break;
        case APP_STATE_VALIDATE:
            // Basic validation: check for valid command
            appData.isValid = (appData.requestedCommand == APP_CMD_OPEN || appData.requestedCommand == APP_CMD_CLOSE);
            if (appData.isValid) {
                appData.currentState = APP_STATE_EXECUTE;
            } else {
                appData.currentState = APP_STATE_ERROR;
            }
            break;
        case APP_STATE_EXECUTE:
            // Process the command, set actuator states
            if (appData.requestedCommand == APP_CMD_OPEN) {
                Hal_SetMotorDirection(1);
            } else if (appData.requestedCommand == APP_CMD_CLOSE) {
                Hal_SetMotorDirection(-1);
            } else {
                Hal_StopMotor();
            }
            appData.outputRequest = 1;
            appData.currentState = APP_STATE_OUTPUT;
            break;
        case APP_STATE_OUTPUT:
            if (appData.outputRequest) {
                Hal_SetLedState(1);
                appData.outputRequest = 0;
            }
            appData.currentState = APP_STATE_IDLE;
            break;
        case APP_STATE_ERROR:
        default:
            Hal_StopMotor();
            Hal_SetLedState(0);
            appData.currentState = APP_STATE_IDLE;
            break;
    }
}
