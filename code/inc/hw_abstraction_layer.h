#ifndef HW_ABSTRACTION_LAYER_H
#define HW_ABSTRACTION_LAYER_H

typedef enum {
    HAL_INIT,
    HAL_OPERATIONAL,
    HAL_FAULT
} HalState_t;

typedef struct {
    int adc_regs[8];
    int uart_regs[2];
    int gpio_regs[4];
    int pwm_regs[2];
} HardwareAbstractionData_t;

void HAL_Init(void);
void HAL_ForwardCall(int caller, int param);

#endif // HW_ABSTRACTION_LAYER_H
