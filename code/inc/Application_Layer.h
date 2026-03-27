#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

// Enum for Application State Machine
typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_COMMAND_RECEIVED,
    APP_STATE_VALIDATING,
    APP_STATE_EXECUTING,
    APP_STATE_OUTPUT_TRIGGERED,
    APP_STATE_ERROR
} ApplicationState_t;

// Structure for User Command
typedef struct {
    int command_id;
    int command_param;
} UserCommand_t;

// Structure for application status
typedef struct {
    ApplicationState_t state;
    int validation_ok;
    int pending_output;
    UserCommand_t last_command;
} ApplicationStatus_t;

// Init function
void ApplicationLayer_Init(ApplicationStatus_t *status);

// Process function (command processing, input validation, logic, output activation)
void ApplicationLayer_Process(ApplicationStatus_t *status, const UserCommand_t *input_command);

// State output API
ApplicationState_t ApplicationLayer_GetState(const ApplicationStatus_t *status);

#endif // APPLICATION_LAYER_H
