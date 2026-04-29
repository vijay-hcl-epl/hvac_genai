#include "init_coordinator.h"
#include "command_handler.h"
#include "feedback_acquisition.h"
#include "motor_controller.h"
#include "indication_manager.h"
#include <stdint.h>
#include <stdbool.h>
// Hardware abstraction stubs (replace with HAL includes as appropriate)
static SystemStatus status = {SYS_STATE_INIT, 0U, 0U, false};

void system_init(void) {
    // Initialize UART, ADC, GPIO, PWM - hardware specific
    // HAL_UART_Init(...);
    // HAL_ADC_Init(...);
    // HAL_GPIO_Init(...);
    // HAL_TIM_PWM_Init(...);
    motor_stop();
    // Get initial position
    bool ok = false;
    uint8_t pos = 0U;
    (void)feedback_acquire(&pos, &ok);
    status.current_pos = pos;
    status.position_valid = ok;
    status.state = ok ? SYS_STATE_IDLE : SYS_STATE_INVALID_FEEDBACK;
    indication_update(status.current_pos, status.position_valid);
}

void main_loop(void) {
    bool valid = false;
    uint8_t pos = 0U;
    (void)feedback_acquire(&pos, &valid);
    status.current_pos = pos;
    status.position_valid = valid;
    if (!valid) {
        status.state = SYS_STATE_INVALID_FEEDBACK;
        motor_stop();
        indication_update(status.current_pos, false);
        return;
    }
    
    uint8_t cmd = 0xFFU;
    CmdParseStatus cstat = command_handler_poll(&cmd);
    if (cstat == CMD_PARSE_OK && cmd != status.current_pos) {
        status.target_pos = cmd;
        status.state = SYS_STATE_MOVING;
        motor_set(status.target_pos, status.current_pos, true);
    } else if (status.state == SYS_STATE_MOVING) {
        if (status.current_pos == status.target_pos) {
            status.state = SYS_STATE_IDLE;
            motor_stop();
        } else {
            motor_set(status.target_pos, status.current_pos, true);
        }
    }
    indication_update(status.current_pos, true);
}
