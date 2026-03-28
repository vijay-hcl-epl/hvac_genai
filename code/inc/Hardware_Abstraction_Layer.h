#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H
#include <stdint.h>

typedef struct {
    uint8_t peripheral_ready;
    uint8_t powerup_state;
} hal_status_t;

void HAL_Init(void);
void HAL_Task(void);
uint8_t HAL_IsReady(void);

#endif // HARDWARE_ABSTRACTION_LAYER_H
