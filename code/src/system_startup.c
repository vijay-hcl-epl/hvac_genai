#include "system_startup.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "feedback_processor.h"
#include "led_status_handler.h"

void system_init(void) {
    command_parser_init();
    motor_init();
    feedback_processor_init();
    flap_control_init();
    led_status_handler_init();
    led_power_on();
}
