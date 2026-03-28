#include "Hardware_Abstraction_Layer.h"

static hal_status_t hal_status = {0, 0};

void HAL_Init(void) {
    hal_status.peripheral_ready = 1;
    hal_status.powerup_state = 1;
}

void HAL_Task(void) {
    // Status processing
}

uint8_t HAL_IsReady(void) {
    return hal_status.peripheral_ready;
}
