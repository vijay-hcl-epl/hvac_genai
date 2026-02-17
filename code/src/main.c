#include "uart_lin_driver.h"
#include "adc_driver.h"
#include "motor_driver.h"
#include "gpio_led_hs_driver.h"
#include "cmd_interpreter.h"
#include "flap_position_ctrl.h"
#include "state_manager.h"
#include "fault_handler.h"
#include "user_interface.h"
#include "test_monitor.h"
#include <stdint.h>

int main(void)
{
    SerialConfig scfg = { UART_MODE, 9600 };
    Serial_init(&scfg);
    ADC_Config acfg = {10, 0};
    ADC_init(&acfg);
    MotorConfig mcfg = {1000, 100, MOTOR_STOP};
    Motor_init(&mcfg);
    GPIO_init();
    UI_init();

    while (1) {
        // [TBD — call polling handlers/event FSM]
        Fault_check();
    }
    return 0;
}
