#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

// State definitions
typedef enum {
    STATE_IDLE,
    STATE_VALIDATE,
    STATE_EXECUTE,
    STATE_OUTPUT,
    STATE_ERROR
} AppState_t;

// Application Layer static data
static AppState_t app_state;
static int app_requested_command;
static int app_validation_status;
static int app_output_request_state;

// Function prototypes
void Application_Init(void);
void Application_Process(void);

#endif // APPLICATION_LAYER_H
