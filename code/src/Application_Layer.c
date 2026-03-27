#include "Application_Layer.h"

static AppState_t appState = APP_STATE_IDLE;
static AppCommand_t appCmd = {0};

void ApplicationLayer_Init(void) {
    appState = APP_STATE_IDLE;
    appCmd.command = 0;
    appCmd.validated = 0;
    appCmd.output_pending = 0;
}

void ApplicationLayer_ReceiveCommand(int cmd) {
    if (appState == APP_STATE_IDLE) {
        appCmd.command = cmd;
        appState = APP_STATE_COMMAND_RECEIVED;
    }
}

// Internal validation (simple example; expand as needed)
static int validateCommand(int cmd) {
    // Accept positive commands only
    return (cmd > 0) ? 1 : 0;
}

void ApplicationLayer_Process(void) {
    switch (appState) {
        case APP_STATE_IDLE:
            // Waiting for command
            break;

        case APP_STATE_COMMAND_RECEIVED:
            if (validateCommand(appCmd.command)) {
                appCmd.validated = 1;
                appState = APP_STATE_VALIDATING;
            } else {
                appState = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_VALIDATING:
            // After validation, process
            if (appCmd.validated) {
                appState = APP_STATE_EXECUTING;
            } else {
                appState = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_EXECUTING:
            // Execute logic
            appCmd.output_pending = 1;
            appState = APP_STATE_OUTPUT_TRIGGERED;
            break;

        case APP_STATE_OUTPUT_TRIGGERED:
            // Trigger output (for now, reset)
            appCmd.output_pending = 0;
            appState = APP_STATE_IDLE;
            break;

        case APP_STATE_ERROR:
            // Handle error
            ApplicationLayer_Init();
            break;
    }
}

AppState_t ApplicationLayer_GetState(void) {
    return appState;
}
