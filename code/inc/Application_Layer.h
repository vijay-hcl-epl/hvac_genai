#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H
#include <stdint.h>

typedef enum {
    APP_IDLE,
    APP_CMD_RECEIVED,
    APP_MOVE_FLAP,
    APP_FLAP_IN_POSITION
} app_state_t;

void APP_Init(void);
void APP_Task(void);
void APP_ReceivePosition(uint16_t adc_value);

#endif // APPLICATION_LAYER_H
