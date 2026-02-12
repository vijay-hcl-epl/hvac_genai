#include "main_coordinator.h"
#include "uart_cmd_handler.h"
#include "motor_control.h"
#include "feedback_processor.h"
#include "led_control.h"

static coordinator_state_t state;

void coordinator_init(void)
{
    uart_cmd_init();
    motor_control_init();
    feedback_processor_init();
    led_control_init();
    state.mode = SYS_INIT;
    state.target_position = FLAP_POSITION_INVALID;
    state.last_position = FLAP_POSITION_INVALID;
    state.error_flag = 0u;
    // Read current position, update LEDs, enter IDLE
    int8_t curr_pos = feedback_get_position();
    state.last_position = curr_pos;
    led_update(curr_pos);
    state.mode = SYS_IDLE;
}

void coordinator_main_loop(void)
{
    int8_t cmd = uart_cmd_get();
    int8_t curr_pos = feedback_get_position();
    if (state.mode == SYS_IDLE)
    {
        if ((cmd >= 0) && (cmd < FLAP_POSITION_COUNT) && (cmd != curr_pos))
        {
            state.target_position = cmd;
            state.mode = SYS_MOVING;
            (void)motor_move_to(cmd);
        }
        else if ((cmd >= 0) && (cmd < FLAP_POSITION_COUNT))
        {
            led_update(curr_pos);
        }
    }
    else if (state.mode == SYS_MOVING)
    {
        if ((curr_pos == state.target_position) && (curr_pos != FLAP_POSITION_INVALID))
        {
            motor_stop();
            state.mode = SYS_HOLD;
            led_update(curr_pos);
        }
        else if (curr_pos == FLAP_POSITION_INVALID)
        {
            motor_stop();
            state.error_flag = 1u;
            state.mode = SYS_IDLE;
        }
    }
    else if (state.mode == SYS_HOLD)
    {
        state.mode = SYS_IDLE;
        state.target_position = FLAP_POSITION_INVALID;
    }
    if (curr_pos != state.last_position)
    {
        led_update(curr_pos);
        state.last_position = curr_pos;
    }
}
