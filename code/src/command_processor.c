#include "command_processor.h"
#include <string.h>

CommandValidationResult_t ValidateUserCommand(const UserCommand_t* cmd) {
    // SWE-REQ-001: Process and validate user command inputs.
    if (cmd == NULL || cmd->data_len == 0 || cmd->data_len > 8) {
        return CMD_INVALID;
    }
    // Example validation: command_id must be in [1,10]
    if (cmd->command_id < 1 || cmd->command_id > 10) {
        return CMD_INVALID;
    }
    // Further validation logic as needed
    return CMD_VALID;
}

ApplicationState_t ProcessApplicationLogic(ApplicationState_t current_state, const UserCommand_t* cmd, CommandValidationResult_t validation) {
    // SWE-REQ-002: Maintain application logic for controlling state transitions.
    if (validation == CMD_INVALID) {
        return STATE_ERROR;
    }
    switch (current_state) {
        case STATE_IDLE:
            return STATE_ACTIVE;
        case STATE_ACTIVE:
            // Stay active; could add logic on command_id
            return STATE_ACTIVE;
        case STATE_ERROR:
        default:
            return STATE_IDLE; // Recover to idle
    }
}

bool InitiateOutputActivation(const ProcessedCommandResult_t* result) {
    // SWE-REQ-003: Initiate output activation based on processed inputs.
    if (!result || result->validation_result != CMD_VALID) {
        return false;
    }
    // Example: activate output if next state is ACTIVE
    return (result->next_state == STATE_ACTIVE);
}

void ProcessAndExecuteUserCommand(ApplicationState_t* current_state, const UserCommand_t* cmd) {
    ProcessedCommandResult_t result;
    result.validation_result = ValidateUserCommand(cmd);
    result.next_state = ProcessApplicationLogic(*current_state, cmd, result.validation_result);
    result.activate_output = InitiateOutputActivation(&result);

    // Update application state
    *current_state = result.next_state;
    // Output activation (application-specific action)
    if (result.activate_output) {
        // Place for hardware/output actuation code
        // e.g., set actuator, send CAN, etc.
        // For ASPICE compliance, code is deterministic and only based on above logic
    }
}
