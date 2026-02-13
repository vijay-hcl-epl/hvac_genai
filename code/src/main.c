#include "hal_uart.h"
#include "hal_adc.h"
#include "hal_pwm.h"
#include "hal_gpio.h"
#include "uart_cmd_if.h"
#include "cmd_proc.h"
#include "flap_pos_ctrl.h"
#include "motor_ctrl.h"
#include "pos_fb_acq.h"
#include "led_stat.h"

int main(void) {
    hal_uart_init();
    hal_adc_init();
    hal_pwm_init();
    uint8_t pin; /* MISRA: Rule 17.8 – Declare iterator at function top */
    for (pin = 0U; pin < 8U; pin++) { /* MISRA: Rule 10.6 – Use suffix for unsigned constants, use braces */
        hal_gpio_set_dir_output(pin);
    }
    uart_cmd_if_init();
    cmd_proc_init();
    flap_pos_ctrl_init();
    motor_ctrl_init();
    pos_fb_acq_init();
    led_stat_init();
    while (1) {
        uart_cmd_if_rx_handler();
        cmd_proc_next();
        /* Could add watchdog here */
    }
    return 0;
}
