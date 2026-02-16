#include "system_initialization.h"
#include "uart_command_handler.h"
#include "flap_actuator_controller.h"
#include "motor_control_unit.h"
#include "position_monitoring_unit.h"
#include "led_indication.h"
static bool init_ok = false;

void system_init(void) {
    uart_command_handler_init();
    led_indication_init();
    position_monitor_init();
    motor_control_init();
    flap_actuator_controller_init();
    init_ok = true;
}

bool system_is_init_ok(void) {
    return init_ok;
}
