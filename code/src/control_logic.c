#include "control_logic.h"
#include "state_manager.h"
#include "position_sensing.h"
#include "motor_driver.h"

static uint8_t target_position = POSITION_INVALID;
static bool moving = false;

void control_logic_init(void)
{
    target_position = POSITION_INVALID;
    moving = false;
}

void control_logic_move_to_position(uint8_t pos)
{
    target_position = pos;
    moving = true;
    state_manager_set_state(STATE_MOVING);

    uint8_t curr = position_sensing_get_current_position();
    if(curr == POSITION_INVALID || pos == curr)
    {
        moving = false;
        state_manager_set_state(STATE_HOLDING);
        motor_driver_disable();
        return;
    }
    else if (curr < pos)
    {
        motor_driver_set_direction(MOTOR_DIRECTION_CW);
        motor_driver_enable();
    }
    else if (curr > pos)
    {
        motor_driver_set_direction(MOTOR_DIRECTION_CCW);
        motor_driver_enable();
    }
}

void control_logic_periodic(void)
{
    if(moving)
    {
        uint8_t curr = position_sensing_get_current_position();
        if(curr == POSITION_INVALID)
        {
            motor_driver_disable();
            moving = false;
            state_manager_set_state(STATE_IDLE);
            return;
        }
        if(curr == target_position)
        {
            motor_driver_disable();
            state_manager_set_state(STATE_HOLDING);
            moving = false;
        }
    }
}
