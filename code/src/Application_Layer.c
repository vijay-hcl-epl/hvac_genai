#include "Application_Layer.h"

// Internal validation function
static int ApplicationLayer_ValidateCommand(const UserCommand_t *input_command)
{
    // Basic validation (example): command_id in range
    return (input_command != 0 && input_command->command_id >= 0 && input_command->command_id < 16) ? 1 : 0;
}

void ApplicationLayer_Init(ApplicationStatus_t *status)
{
    if (status == 0) return;
    status->state = APP_STATE_IDLE;
    status->validation_ok = 0;
    status->pending_output = 0;
    status->last_command.command_id = -1;
    status->last_command.command_param = 0;
}

void ApplicationLayer_Process(ApplicationStatus_t *status, const UserCommand_t *input_command)
{
    if (status == 0) return;
    switch (status->state) {
        case APP_STATE_IDLE:
            if (input_command && ApplicationLayer_ValidateCommand(input_command)) {
                status->last_command = *input_command;
                status->state = APP_STATE_COMMAND_RECEIVED;
            }
            break;
        case APP_STATE_COMMAND_RECEIVED:
            status->validation_ok = ApplicationLayer_ValidateCommand(&status->last_command);
            if (status->validation_ok) {
                status->state = APP_STATE_VALIDATING;
            } else {
                status->state = APP_STATE_ERROR;
            }
            break;
        case APP_STATE_VALIDATING:
            // Application logic (example): if valid, execute
            status->pending_output = 1; // Mark output to be triggered (for demonstration)
            status->state = APP_STATE_EXECUTING;
            break;
        case APP_STATE_EXECUTING:
            if (status->pending_output) {
                status->state = APP_STATE_OUTPUT_TRIGGERED;
            }
            break;
        case APP_STATE_OUTPUT_TRIGGERED:
            // Reset for next command (stateless output)
            status->pending_output = 0;
            status->state = APP_STATE_IDLE;
            break;
        case APP_STATE_ERROR:
        default:
            // Stay in error until re-initialized
            break;
    }
}

ApplicationState_t ApplicationLayer_GetState(const ApplicationStatus_t *status)
{
    if (status == 0) return APP_STATE_ERROR;
    return status->state;
}
