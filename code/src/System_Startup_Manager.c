#include "System_Startup_Manager.h"

void System_Startup_Init(SystemStartupManager_t *sm) {
    sm->state = SYS_INIT;
    sm->adc_initialized = 0;
    sm->uart_initialized = 0;
    sm->gpio_initialized = 0;
    sm->pwm_initialized = 0;
}

void System_Startup_Sequence(SystemStartupManager_t *sm) {
    sm->adc_initialized = 1;
    sm->uart_initialized = 1;
    sm->gpio_initialized = 1;
    sm->pwm_initialized = 1;
    sm->state = SYS_READY;
}
