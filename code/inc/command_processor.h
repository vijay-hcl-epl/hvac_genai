#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Enumeration for user command validation result
 */
typedef enum {
    CMD_VALID = 0,
    CMD_INVALID
} CommandValidationResult_t;

/**
 * @brief Enumeration for the system/application states
 */
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE,
    STATE_ERROR
} ApplicationState_t;

/**
 * @brief Structure to represent a user command
 */
typedef struct {
    uint8_t command_id;
    uint8_t data[8];
    uint8_t data_len;
} UserCommand_t;

/**
 * @brief Structure for processed command result
 */
typedef struct {
    CommandValidationResult_t validation_result;
    ApplicationState_t next_state;
    bool activate_output;
} ProcessedCommandResult_t;

// Function declarations
CommandValidationResult_t ValidateUserCommand(const UserCommand_t* cmd);
ApplicationState_t ProcessApplicationLogic(ApplicationState_t current_state, const UserCommand_t* cmd, CommandValidationResult_t validation);
bool InitiateOutputActivation(const ProcessedCommandResult_t* result);
void ProcessAndExecuteUserCommand(ApplicationState_t* current_state, const UserCommand_t* cmd);

#endif // COMMAND_PROCESSOR_H
