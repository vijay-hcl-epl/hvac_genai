#ifndef INITIALIZATIONSTARTUPUNIT_H
#define INITIALIZATIONSTARTUPUNIT_H

typedef struct {
    int adc_init_done;
    int uart_init_done;
    int gpio_init_done;
    int pwm_init_done;
    int status;
} PeripheralInitStatus;

typedef struct {
    int motor_off_on_init;
    int detected_flap_position_init;
} MotorLedInitStatus;

typedef enum {
    PeripheralsInit,
    StartupIndication
} InitializationStartupState;

void InitializationStartupUnit_resp_1();
void InitializationStartupUnit_resp_2();

#endif
