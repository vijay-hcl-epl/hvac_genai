#include "command_handler.h"
#include "position_manager.h"
#include "flap_control.h"
#include "motor_driver.h"
#include "position_feedback.h"
#include "status_indicator.h"
#include "uart_drv.h"
int main(void) {
    command_handler_init();
    position_manager_init();
    flap_control_init();
    motor_driver_init();
    position_feedback_init();
    status_indicator_init();
    uart_drv_init();
    while(1) {
        uint8_t cmd = UART_read_byte();
        validate_and_dispatch(cmd);
    }
    return 0;
}
