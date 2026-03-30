#include "application_layer.h"
#include <string.h>

void app_init(ApplicationLayer* app) {
    memset(app->command_buffer, 0, sizeof(app->command_buffer));
    app->state = APP_STATE_IDLE;
    app->feedback_data = 0;
}

void app_process_command(ApplicationLayer* app, const char* cmd) {
    strncpy(app->command_buffer, cmd, sizeof(app->command_buffer) - 1);
    // Parsing and state update logic here
    // For example: if recognized, set state to MOVING, etc.
    // else: set state to ERRORHANDLING
}

void app_update_state(ApplicationLayer* app) {
    switch(app->state) {
        case APP_STATE_IDLE:
            // Wait for command
            break;
        case APP_STATE_MOVING:
            // Process moving logic
            app->state = APP_STATE_MONITORING;
            break;
        case APP_STATE_MONITORING:
            // Monitor feedback, decide if needs to move to Idle or ErrorHandling
            break;
        case APP_STATE_ERRORHANDLING:
            app_handle_error(app);
            break;
        default:
            break;
    }
}

void app_handle_error(ApplicationLayer* app) {
    // Error handling logic
    app->state = APP_STATE_IDLE;
}
