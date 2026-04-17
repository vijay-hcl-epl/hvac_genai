#include "command_handler.h"
#include "position_control.h"
#include "motor_driver_if.h"
#include "adc_interface.h"
#include "led_status.h"
#include "error_handling.h"
#include <stdint.h>
int main(void)
{
    command_handler_init();
    position_control_init();
    motor_driver_if_init();
    adc_interface_init();
    led_status_init();
    error_handling_init();
    led_status_power_on();
    // Main loop stub
    while (1)
    {
        // Emulate UART RX event (replace with ISR / event driven)
        if (command_handler_command_ready())
        {
            int8_t cmd = get_valid_command();
            if (cmd >= 0 && cmd <= 5)
                position_control_set_target((uint8_t)cmd);
        }
        position_control_execute();
        // Add periodic ADC sampling, error check, LED update, etc here
    }
    return 0;
}
