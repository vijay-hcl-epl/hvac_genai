#include "Application_Layer.h"

// Internal function prototypes
static void validate_input(ApplicationContext_t *ctx, const UserCommand_t *cmd);
static void process_logic(ApplicationContext_t *ctx, const UserCommand_t *cmd);
static void trigger_outputs(ApplicationContext_t *ctx);
static void set_error(ApplicationContext_t *ctx);

void ApplicationLayer_Init(ApplicationContext_t *ctx) {
    if (ctx) {
        ctx->state = APP_STATE_IDLE;
        ctx->validation_status = 0;
        ctx->output_triggered = 0;
        ctx->last_command.command_id = 0;
        ctx->last_command.param = 0;
    }
}

void ApplicationLayer_ProcessCommand(ApplicationContext_t *ctx, const UserCommand_t *cmd) {
    if (!ctx || !cmd) return;
    ctx->last_command = *cmd;
    ctx->state = APP_STATE_COMMAND_RECEIVED;

    validate_input(ctx, cmd);
    if (ctx->validation_status == 0) {
        ctx->state = APP_STATE_VALIDATING;
        process_logic(ctx, cmd);
        trigger_outputs(ctx);
        ctx->state = APP_STATE_OUTPUT_TRIGGERED;
    } else {
        set_error(ctx);
    }
}

ApplicationState_t ApplicationLayer_GetState(const ApplicationContext_t *ctx) {
    return ctx ? ctx->state : APP_STATE_ERROR;
}

uint8_t ApplicationLayer_GetOutputStatus(const ApplicationContext_t *ctx) {
    return ctx ? ctx->output_triggered : 0;
}

// Internal static implementations
static void validate_input(ApplicationContext_t *ctx, const UserCommand_t *cmd) {
    if (!cmd || cmd->command_id == 0xFF) {
        ctx->validation_status = 1; // invalid
    } else {
        ctx->validation_status = 0; // valid
    }
}

static void process_logic(ApplicationContext_t *ctx, const UserCommand_t *cmd) {
    // Placeholder logic - process based only on supplied struct
dash if (cmd->command_id == 1 && cmd->param < 100) {
        ctx->output_triggered = 1;
        ctx->state = APP_STATE_EXECUTING;
    } else {
        ctx->output_triggered = 0;
        ctx->state = APP_STATE_EXECUTING;
    }
}

static void trigger_outputs(ApplicationContext_t *ctx) {
    // Directly update output_triggered, already handled in process_logic
}

static void set_error(ApplicationContext_t *ctx) {
    ctx->state = APP_STATE_ERROR;
    ctx->output_triggered = 0;
}
