#ifndef APPLICATIONLAYER_H
#define APPLICATIONLAYER_H

typedef enum {
    WAIT_FOR_COMMAND,
    VALIDATE_COMMAND,
    ISSUE_TO_SIGNAL_MANAGER,
    IDLE
} AppLayerState_t;

typedef struct {
    char uart_cmd_buffer[16];
    int cmd_valid;
    int target_position;
    AppLayerState_t state;
} ApplicationLayer_t;

void AppLayer_Init(ApplicationLayer_t* instance);
void AppLayer_Run(ApplicationLayer_t* instance);

#endif // APPLICATIONLAYER_H
