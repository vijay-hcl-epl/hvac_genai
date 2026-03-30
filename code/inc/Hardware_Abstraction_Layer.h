#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    HAL_STATE_INIT,
    HAL_STATE_READY,
    HAL_STATE_ERROR
} HalState_t;

typedef struct {
    int io_status;
    int error_flag;
    int health_flag;
    HalState_t state;
} HardwareAbstractionLayer_t;

void HAL_Init(HardwareAbstractionLayer_t* hal);
void HAL_Monitor(HardwareAbstractionLayer_t* hal);

#endif
