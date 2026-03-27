#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

#include <stdint.h>

// HAL State
typedef enum {
    HAL_STATE_IDLE,
    HAL_STATE_MOVING
} HAL_State_t;

typedef struct {
    HAL_State_t state;
    uint8_t physical_position;
} HardwareAbstractionLayer_t;

void HardwareAbstractionLayer_Init(HardwareAbstractionLayer_t *ctx);
void HardwareAbstractionLayer_MoveFlap(uint8_t position);
int  HardwareAbstractionLayer_IsMoveComplete(void);

#endif // HARDWARE_ABSTRACTION_LAYER_H
