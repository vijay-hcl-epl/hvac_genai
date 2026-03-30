#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    HAL_STATE_READY,
    HAL_STATE_BUSY,
    HAL_STATE_IDLE
} HalState_t;

typedef struct {
    int handle_table[8];
    int logic_map[8];
} HalHandle_t;

void HardwareAbstractionLayer_Init(HalHandle_t* h);
int HardwareAbstractionLayer_Command(HalHandle_t* h, int logic_cmd);

#endif // HARDWARE_ABSTRACTION_LAYER_H
