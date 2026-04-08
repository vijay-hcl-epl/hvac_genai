#ifndef SYSTEM_STARTUP_MANAGER_H
#define SYSTEM_STARTUP_MANAGER_H

typedef enum {
    SYS_INIT,
    SYS_READY
} SystemStartupState_t;

typedef struct {
    SystemStartupState_t state;
    int adc_initialized;
    int uart_initialized;
    int gpio_initialized;
    int pwm_initialized;
} SystemStartupManager_t;

void System_Startup_Init(SystemStartupManager_t *sm);
void System_Startup_Sequence(SystemStartupManager_t *sm);

#endif // SYSTEM_STARTUP_MANAGER_H
