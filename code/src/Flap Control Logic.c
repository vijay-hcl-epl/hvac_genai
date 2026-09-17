#include "Flap Control Logic.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "LED Status Handler.h"
#include "Motor Driver.h"

typedef enum
{
    FLAP_CONTROL_STATE_IDLE = 0,
    FLAP_CONTROL_STATE_MOVING,
    FLAP_CONTROL_STATE_TARGET_REACHED,
    FLAP_CONTROL_STATE_FAULT
} Flap_Control_StateType;

static Flap_Control_StateType Flap_Control_State = FLAP_CONTROL_STATE_IDLE;
static uint8_t Flap_Control_CurrentPosition = 0U;
static uint8_t Flap_Control_TargetPosition = 0U;
static bool Flap_Control_InMotion = false;

void Flap_Control_Logic_Init(void)
{
    Flap_Control_State = FLAP_CONTROL_STATE_IDLE;
    Flap_Control_CurrentPosition = 0U;
    Flap_Control_TargetPosition = 0U;
    Flap_Control_InMotion = false;
}

void Flap_Control_Logic_IssueMovementCmd(uint8_t target_position)
{
    uint8_t feedback_position = 0U;

    if (Feedback_Processor_GetPosition(&feedback_position) == false)
    {
        Motor_Driver_StopMotor();
        LED_Status_Handler_IndicateError();
        Flap_Control_InMotion = false;
        Flap_Control_State = FLAP_CONTROL_STATE_FAULT;
    }
    else
    {
        Flap_Control_CurrentPosition = feedback_position;
        Flap_Control_TargetPosition = target_position;

        if (Flap_Control_TargetPosition == Flap_Control_CurrentPosition)
        {
            Motor_Driver_StopMotor();
            LED_Status_Handler_SetLedState(Flap_Control_CurrentPosition);
            Flap_Control_InMotion = false;
            Flap_Control_State = FLAP_CONTROL_STATE_TARGET_REACHED;
        }
        else if (Flap_Control_TargetPosition > Flap_Control_CurrentPosition)
        {
            Motor_Driver_DriveMotor(MOTOR_DRIVER_DIR_OPEN, true);
            Flap_Control_InMotion = true;
            Flap_Control_State = FLAP_CONTROL_STATE_MOVING;
        }
        else
        {
            Motor_Driver_DriveMotor(MOTOR_DRIVER_DIR_CLOSE, true);
            Flap_Control_InMotion = true;
            Flap_Control_State = FLAP_CONTROL_STATE_MOVING;
        }
    }
}

void Flap_Control_Logic_MainTask(void)
{
    uint8_t command_position = 0U;
    uint8_t feedback_position = 0U;

    Command_Parser_Update();
    Feedback_Processor_Update();

    if (Feedback_Processor_GetPosition(&feedback_position) == false)
    {
        Motor_Driver_StopMotor();
        LED_Status_Handler_IndicateError();
        Flap_Control_InMotion = false;
        Flap_Control_State = FLAP_CONTROL_STATE_FAULT;
    }
    else
    {
        Flap_Control_CurrentPosition = feedback_position;

        if (Command_Parser_GetLatestCommand(&command_position) == true)
        {
            Flap_Control_Logic_IssueMovementCmd(command_position);
            Command_Parser_Clear();
        }
        else if (Flap_Control_InMotion == true)
        {
            if (Flap_Control_CurrentPosition == Flap_Control_TargetPosition)
            {
                Motor_Driver_StopMotor();
                LED_Status_Handler_SetLedState(Flap_Control_CurrentPosition);
                Flap_Control_InMotion = false;
                Flap_Control_State = FLAP_CONTROL_STATE_TARGET_REACHED;
            }
            else if (Flap_Control_TargetPosition > Flap_Control_CurrentPosition)
            {
                Motor_Driver_DriveMotor(MOTOR_DRIVER_DIR_OPEN, true);
                Flap_Control_State = FLAP_CONTROL_STATE_MOVING;
            }
            else
            {
                Motor_Driver_DriveMotor(MOTOR_DRIVER_DIR_CLOSE, true);
                Flap_Control_State = FLAP_CONTROL_STATE_MOVING;
            }
        }
        else
        {
            Flap_Control_State = FLAP_CONTROL_STATE_IDLE;
        }
    }
}

bool Flap_Control_Logic_IsInMotion(void)
{
    return Flap_Control_InMotion;
}

uint8_t Flap_Control_Logic_GetTargetPosition(void)
{
    return Flap_Control_TargetPosition;
}
