#include "Flap Control Logic.h"
#include "Feedback Processor.h"
#include "Motor Driver.h"
#include "LED Status Handler.h"

#define FLAG_FALSE                    (0U)
#define FLAG_TRUE                     (1U)
#define POSITION_INVALID              (255U)

typedef struct
{
    uint8_t current_position;
    uint8_t target_position;
    uint8_t last_led_position;
    uint8_t in_motion;
    Flap_Control_State_t state;
} Flap_Control_Data_t;

static Flap_Control_Data_t flap_control;

static uint8_t Flap_Control_Is_Position_Valid(uint8_t position)
{
    uint8_t result = FLAG_FALSE;

    if ((position >= FLAP_POSITION_MIN) && (position <= FLAP_POSITION_MAX))
    {
        result = FLAG_TRUE;
    }

    return result;
}

static void Flap_Control_Stop_At_Position(uint8_t position)
{
    Motor_Driver_Stop();
    flap_control.current_position = position;
    flap_control.in_motion = FLAG_FALSE;
    flap_control.state = FLAP_CONTROL_TARGET_REACHED;
    if (flap_control.last_led_position != position)
    {
        LED_Status_Handler_Set_Led_State(position);
        flap_control.last_led_position = position;
    }
}

void Flap_Control_Logic_Init(void)
{
    flap_control.current_position = 0U;
    flap_control.target_position = 0U;
    flap_control.last_led_position = POSITION_INVALID;
    flap_control.in_motion = FLAG_FALSE;
    flap_control.state = FLAP_CONTROL_IDLE;
}

void Flap_Control_Logic_Process_Command(uint8_t target_position)
{
    uint8_t current = 0U;
    uint8_t feedback_valid = FLAG_FALSE;

    if (Flap_Control_Is_Position_Valid(target_position) == FLAG_TRUE)
    {
        Feedback_Processor_Get_Position(&current, &feedback_valid);
        flap_control.target_position = target_position;

        if (feedback_valid == FLAG_FALSE)
        {
            Motor_Driver_Stop();
            LED_Status_Handler_Indicate_Error();
            flap_control.in_motion = FLAG_FALSE;
            flap_control.state = FLAP_CONTROL_FAULT;
        }
        else if (current == target_position)
        {
            Flap_Control_Stop_At_Position(current);
        }
        else
        {
            flap_control.current_position = current;
            flap_control.in_motion = FLAG_TRUE;
            flap_control.state = FLAP_CONTROL_MOVING;
            if (target_position > current)
            {
                Motor_Driver_Drive(MOTOR_DIRECTION_OPEN, FLAG_TRUE);
            }
            else
            {
                Motor_Driver_Drive(MOTOR_DIRECTION_CLOSE, FLAG_TRUE);
            }
        }
    }
}

void Flap_Control_Logic_MainFunction(void)
{
    uint8_t current = 0U;
    uint8_t feedback_valid = FLAG_FALSE;

    Feedback_Processor_Update();
    Feedback_Processor_Get_Position(&current, &feedback_valid);

    if (feedback_valid == FLAG_FALSE)
    {
        Motor_Driver_Stop();
        LED_Status_Handler_Indicate_Error();
        flap_control.in_motion = FLAG_FALSE;
        flap_control.state = FLAP_CONTROL_FAULT;
    }
    else
    {
        flap_control.current_position = current;
        if (flap_control.state == FLAP_CONTROL_FAULT)
        {
            flap_control.state = FLAP_CONTROL_IDLE;
        }

        if (flap_control.in_motion == FLAG_TRUE)
        {
            if (current == flap_control.target_position)
            {
                Flap_Control_Stop_At_Position(current);
            }
            else if (flap_control.target_position > current)
            {
                Motor_Driver_Drive(MOTOR_DIRECTION_OPEN, FLAG_TRUE);
            }
            else
            {
                Motor_Driver_Drive(MOTOR_DIRECTION_CLOSE, FLAG_TRUE);
            }
        }
        else if (flap_control.last_led_position != current)
        {
            LED_Status_Handler_Set_Led_State(current);
            flap_control.last_led_position = current;
            flap_control.state = FLAP_CONTROL_IDLE;
        }
        else
        {
            flap_control.state = FLAP_CONTROL_IDLE;
        }
    }
}

Flap_Control_State_t Flap_Control_Logic_Get_State(void)
{
    return flap_control.state;
}
