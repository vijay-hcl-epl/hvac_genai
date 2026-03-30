#include "ApplicationLayer.h"
#include "SignalIfManager.h"
static AppLayerData appData;
static AppState appState;
void ApplicationLayer_Init(void)
{
    appData.current_position = 0U;
    appData.target_position = 0U;
    appData.error_flag = 0U;
    appState = APP_STATE_IDLE;
}
void ApplicationLayer_Task(void)
{
    switch(appState)
    {
        case APP_STATE_IDLE:
            // Wait for command
            break;
        case APP_STATE_WAITING_FOR_COMMAND:
            // Set target, command movement
            appState = APP_STATE_MOVING_TO_POSITION;
            break;
        case APP_STATE_MOVING_TO_POSITION:
            if (SignalIfManager_GetPosition() == appData.target_position)
            {
                appState = APP_STATE_TARGET_REACHED;
            }
            break;
        case APP_STATE_TARGET_REACHED:
            SignalIfManager_StopMotor();
            appState = APP_STATE_IDLE;
            break;
        case APP_STATE_ERROR_HANDLING:
            SignalIfManager_StopMotor();
            break;
        default:
            break;
    }
}
void ApplicationLayer_OnCommand(uint8_t pos)
{
    if(pos <= 5U)
    {
        appData.target_position = pos;
        appState = APP_STATE_WAITING_FOR_COMMAND;
    }
    else
    {
        appData.error_flag = 1U;
        appState = APP_STATE_ERROR_HANDLING;
    }
}
