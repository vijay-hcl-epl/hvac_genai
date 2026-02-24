#include "flap_controller.h"
#include "command_handler.h"
#include "position_feedback.h"
#include "motor_control.h"
#include <stdint.h>
#include <stdbool.h>

static int current_target = 0;
static FlapControllerState_t flap_state = FLAP_CTRL_IDLE;

void FlapController_Init(void)
{
    current_target = 0;
    flap_state = FLAP_CTRL_IDLE;
}

void FlapController_Tick(void)
{
    int cmd;
    uint8_t cur_pos;
    bool valid_cmd = CommandHandler_GetLastCommand(&cmd);
    bool valid_pos = PositionFeedback_GetPosition(&cur_pos);
    bool feedback_ok = PositionFeedback_IsValid();

    switch (flap_state)
    {
    case FLAP_CTRL_IDLE:
        if (valid_cmd && valid_pos)
        {
            current_target = cmd;
            if (cur_pos != current_target)
            {
                flap_state = FLAP_CTRL_MOVING;
                if (cur_pos < current_target)
                {
                    MotorControl_ApplyOrder(CTRL_ORDER_MOVE_CW);
                }
                else
                {
                    MotorControl_ApplyOrder(CTRL_ORDER_MOVE_CCW);
                }
            }
            else
            {
                flap_state = FLAP_CTRL_TARGET_REACHED;
                MotorControl_ApplyOrder(CTRL_ORDER_STOP);
            }
        }
        break;
    case FLAP_CTRL_MOVING:
        if (!feedback_ok)
        {
            MotorControl_ApplyOrder(CTRL_ORDER_STOP);
            flap_state = FLAP_CTRL_IDLE;
            break;
        }
        if (valid_pos && cur_pos == current_target)
        {
            MotorControl_ApplyOrder(CTRL_ORDER_STOP);
            flap_state = FLAP_CTRL_TARGET_REACHED;
        }
        break;
    case FLAP_CTRL_TARGET_REACHED:
        if (!feedback_ok)
        {
            MotorControl_ApplyOrder(CTRL_ORDER_STOP);
            flap_state = FLAP_CTRL_IDLE;
            break;
        }
        // Wait for new command
        if (valid_cmd && valid_pos && cur_pos != current_target)
        {
            flap_state = FLAP_CTRL_MOVING;
            if (cur_pos < current_target)
            {
                MotorControl_ApplyOrder(CTRL_ORDER_MOVE_CW);
            }
            else
            {
                MotorControl_ApplyOrder(CTRL_ORDER_MOVE_CCW);
            }
        }
        break;
    default:
        MotorControl_ApplyOrder(CTRL_ORDER_STOP);
        flap_state = FLAP_CTRL_IDLE;
        break;
    }
}
