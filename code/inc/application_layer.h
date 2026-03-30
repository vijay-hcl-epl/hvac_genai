#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>
typedef enum {
    APP_STATE_IDLE,
    APP_STATE_MOVING,
    APP_STATE_MONITORING,
    APP_STATE_ERRORHANDLING
} app_state_t;

typedef struct {
    char command_buffer[32];
    app_state_t state;
    uint16_t feedback_data;
} ApplicationLayer;

void app_init(ApplicationLayer* app);
void app_process_command(ApplicationLayer* app, const char* cmd);
void app_update_state(ApplicationLayer* app);
void app_handle_error(ApplicationLayer* app);

#endif // APPLICATION_LAYER_H
