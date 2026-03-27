#include "Application_Layer.h"
#include "Signal_Interface_Manager.h"
#include "Hardware_Abstraction_Layer.h"

static ApplicationLayer_DataType appData;

void Application_Init(void) {
    appData.requestedCommand = 0;
    appData.currentState = STATE_IDLE;
    appData.isCommandValid = 0;
    appData.outputRequestState = 0;
}

void Application_Process(void) {
    switch (appData.currentState) {
        case STATE_IDLE:
            appData.requestedCommand = SignalInterface_ReadCommand();
            appData.currentState = STATE_VALIDATE;
            break;
        case STATE_VALIDATE:
            if (appData.requestedCommand >= 0 && appData.requestedCommand <= 100) {
                appData.isCommandValid = 1;
                appData.currentState = STATE_EXECUTE;
            } else {
                appData.isCommandValid = 0;
                appData.currentState = STATE_ERROR;
            }
            break;
        case STATE_EXECUTE:
            if (appData.isCommandValid) {
                Hal_SetMotorDirection(appData.requestedCommand);
                appData.currentState = STATE_OUTPUT;
            } else {
                appData.currentState = STATE_ERROR;
            }
            break;
        case STATE_OUTPUT:
            Hal_SetLedState(appData.requestedCommand);
            appData.currentState = STATE_IDLE;
            break;
        case STATE_ERROR:
            Hal_StopMotor();
            appData.currentState = STATE_IDLE;
            break;
        default:
            appData.currentState = STATE_IDLE;
            break;
    }
}
