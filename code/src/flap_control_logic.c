#include "flap_control_logic.h"
#include "uart_handler.h"
#include "feedback_processing.h"
#include "motor_driver.h"
static uint8_t target_position = 0;
static uint8_t current_position = 0;
static bool busy_flag = false;
void flap_control_init(void) {
    target_position = 0;
    busy_flag = false;
}
void flap_control_event(void) {
    uint8_t cmd;
    if (!busy_flag && uart_get_valid_command(&cmd)) {
        current_position = feedback_get_position();
        if (cmd <= 5 && cmd != current_position) {
            target_position = cmd;
            busy_flag = true;
            int dir = (cmd > current_position) ? 1 : -1;
            motor_move(dir);
        }
    }
    if (busy_flag && !motor_is_active()) {
        current_position = feedback_get_position();
        if (current_position == target_position) {
            busy_flag = false;
        }
    }
}
bool flap_control_is_busy(void) { return busy_flag; }
uint8_t flap_control_get_target(void) { return target_position; }
