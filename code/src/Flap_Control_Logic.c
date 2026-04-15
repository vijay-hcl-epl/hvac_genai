#include "Flap_Control_Logic.h"
#include "Command_Parser.h"
#include "Feedback_Processor.h"
#include "Motor_Driver.h"
#include "LED_Status_Handler.h"
#include <stdbool.h>

// Internal states
static uint8_t current_pos = 0U;
static uint8_t target_pos = 0U;
static bool in_motion = false;
static bool first_run = true;

void Flap_Control_Logic_Init(void)
{
    in_motion = false;
    target_pos = 0U;
    current_pos = 0U;
    first_run = true;
}

void Flap_Control_Logic_Task(void)
{
    Command_t cmd = Command_Parser_Get_Latest();
    Feedback_Processor_Update();
    bool feedback_ok = Feedback_Processor_Is_Valid();
    uint8_t feedback_pos = Feedback_Processor_Get_Position();

    if (first_run)
    {
        current_pos = feedback_pos;
        target_pos = feedback_pos;
        first_run = false;
        LED_Status_Handler_Set_Position(current_pos);
        Motor_Driver_Stop();
        return;
    }

    if(!feedback_ok)
    {
        Motor_Driver_Stop();
        LED_Status_Handler_Indicate_Error();
        in_motion = false;
        return;
    }

    current_pos = feedback_pos;

    // If no valid command or command matches current position
    if (!cmd.is_valid || (cmd.command_byte == current_pos))
    {
        Motor_Driver_Stop();
        // LED update only on legit pos change (see LLD)
        return;
    }

    if(cmd.command_byte != target_pos)
    {
        // New command, update target
        target_pos = cmd.command_byte;
        in_motion = true;
    }

    if(in_motion)
    {
        // Drive if not at target
        if(current_pos != target_pos)
        {
            if(current_pos < target_pos)
            {
                Motor_Driver_Drive(MOTOR_FORWARD, true);
            }
            else
            {
                Motor_Driver_Drive(MOTOR_REVERSE, true);
            }
        }
        else
        {
            Motor_Driver_Stop();
            LED_Status_Handler_Set_Position(current_pos);
            in_motion = false;
        }
    }
    else
    {
        Motor_Driver_Stop();
    }
}
