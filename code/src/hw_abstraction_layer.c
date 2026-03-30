#include "hw_abstraction_layer.h"

static HardwareAbstractionData_t halData;

void HAL_Init(void) {
    // Set register maps to zero
    for(int i=0; i<8; i++) halData.adc_regs[i]=0;
    for(int i=0; i<2; i++) halData.uart_regs[i]=0;
    for(int i=0; i<4; i++) halData.gpio_regs[i]=0;
    for(int i=0; i<2; i++) halData.pwm_regs[i]=0;
}

void HAL_ForwardCall(int caller, int param) {
    // Forward (dummy)
}
