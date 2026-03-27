#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <stdint.h>

// UART Command Buffer Size
#define UART_CMD_BUFFER_SIZE 16

// State machine enum
typedef enum {
    STATE_IDLE,
    STATE_CMD_RECV,
    STATE_CMD_VALIDATE,
    STATE_FLAP_SETPOINT,
    STATE_ERROR
} AppLayerState_t;

// App Layer Internal Data
typedef struct {
    char uart_rx_buffer[UART_CMD_BUFFER_SIZE];
    uint8_t cmd_length;
    AppLayerState_t state;
    uint8_t target_flap_position;
} ApplicationLayer_t;

void ApplicationLayer_Init(ApplicationLayer_t *ctx);
void ApplicationLayer_Task(ApplicationLayer_t *ctx);

#endif // APPLICATION_LAYER_H
