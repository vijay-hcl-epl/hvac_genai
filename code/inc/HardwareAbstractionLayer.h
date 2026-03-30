#ifndef HARDWAREABSTRACTIONLAYER_H
#define HARDWAREABSTRACTIONLAYER_H

typedef enum {
    HW_IDLE,
    HW_IO_REQUEST,
    HW_UPDATING,
    HW_COMPLETE
} HALState_t;

typedef struct {
    int adc_value;
    int gpio_status;
    int uart_status;
    int led_status;
    HALState_t state;
} HardwareAbstractionLayer_t;

void HAL_Init(HardwareAbstractionLayer_t* instance);
void HAL_Run(HardwareAbstractionLayer_t* instance);
void HAL_ProcessAction(HardwareAbstractionLayer_t* instance, int action);

#endif // HARDWAREABSTRACTIONLAYER_H
