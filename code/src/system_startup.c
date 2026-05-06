#include "system_startup.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "motor_driver.h"
#include "feedback_processor.h"
#include "led_status_handler.h"

void system_startup_init(void) {
    command_parser_init();
    feedback_processor_init();
    motor_driver_init();
    led_status_handler_init();
    flap_control_init();
}
