#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>

// Application State Enum
typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_COMMAND_RECEIVED,
    APP_STATE_VALIDATING,
    APP_STATE_EXECUTING,
    APP_STATE_OUTPUT_TRIGGERED,
    APP_STATE_ERROR
} ApplicationState_t;

// User Command structure
typedef struct {
    uint8_t command_id;
    uint16_t param;
} UserCommand_t;

// Application data context
typedef struct {
    ApplicationState_t state;
    UserCommand_t last_command;
    uint8_t validation_status;
    uint8_t output_triggered;
} ApplicationContext_t;

// Command Processing API
void ApplicationLayer_Init(ApplicationContext_t *ctx);
void ApplicationLayer_ProcessCommand(ApplicationContext_t *ctx, const UserCommand_t *cmd);
ApplicationState_t ApplicationLayer_GetState(const ApplicationContext_t *ctx);
uint8_t ApplicationLayer_GetOutputStatus(const ApplicationContext_t *ctx);

#endif // APPLICATION_LAYER_H
