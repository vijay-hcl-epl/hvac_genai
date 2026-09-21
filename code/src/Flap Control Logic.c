#include "Flap Control Logic.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "LED Status Handler.h"
#include "Motor Driver.h"

/* Flap state and movement decision logic.
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-025, SWE-REQ-031, SWE-REQ-032, SWE-REQ-033.
 */

static FlapControl_State_t FlapControl_State = FLAP_CONTROL_STATE_IDLE;
static Hvac_FlapPosition_t FlapControl_CurrentPosition = HVAC_FLAP_POSITION_INVALID;
static Hvac_FlapPosition_t FlapControl_TargetPosition = HVAC_FLAP_POSITION_INVALID;
static bool FlapControl_InMotion = false;

static MotorDriver_Direction_t FlapControl_GetDirection(Hvac_FlapPosition_t current_pos, Hvac_FlapPosition_t target_pos)
{
    MotorDriver_Direction_t direction = MOTOR_DRIVER_DIRECTION_STOP;

    if ((current_pos != HVAC_FLAP_POSITION_INVALID) && (target_pos != HVAC_FLAP_POSITION_INVALID))
    {
        if ((uint8_t)target_pos > (uint8_t)current_pos)
        {
            direction = MOTOR_DRIVER_DIRECTION_FORWARD;
        }
        else if ((uint8_t)target_pos < (uint8_t)current_pos)
        {
            direction = MOTOR_DRIVER_DIRECTION_REVERSE;
        }
        else
        {
            direction = MOTOR_DRIVER_DIRECTION_STOP;
        }
    }

    return direction;
}

void FlapControlLogic_Init(void)
{
    FlapControl_State = FLAP_CONTROL_STATE_IDLE;
    FlapControl_CurrentPosition = HVAC_FLAP_POSITION_INVALID;
    FlapControl_TargetPosition = HVAC_FLAP_POSITION_INVALID;
    FlapControl_InMotion = false;
}

void FlapControlLogic_IssueMovementCmd(Hvac_FlapPosition_t target_pos)
{
    FeedbackProcessor_Position_t feedback = FeedbackProcessor_GetPosition();
    MotorDriver_Direction_t direction;

    if (feedback.valid == false)
    {
        MotorDriver_StopMotor();
        LedStatusHandler_IndicateError();
        FlapControl_InMotion = false;
        FlapControl_State = FLAP_CONTROL_STATE_FAULT;
    }
    else
    {
        FlapControl_CurrentPosition = feedback.position;
        FlapControl_TargetPosition = target_pos;

        if (FlapControl_CurrentPosition == FlapControl_TargetPosition)
        {
            MotorDriver_StopMotor();
            LedStatusHandler_SetLedState(FlapControl_CurrentPosition);
            FlapControl_InMotion = false;
            FlapControl_State = FLAP_CONTROL_STATE_TARGET_REACHED;
        }
        else
        {
            direction = FlapControl_GetDirection(FlapControl_CurrentPosition, FlapControl_TargetPosition);
            if (direction == MOTOR_DRIVER_DIRECTION_STOP)
            {
                MotorDriver_StopMotor();
                FlapControl_InMotion = false;
                FlapControl_State = FLAP_CONTROL_STATE_IDLE;
            }
            else
            {
                MotorDriver_DriveMotor(direction, true);
                FlapControl_InMotion = true;
                FlapControl_State = FLAP_CONTROL_STATE_MOVING;
            }
        }
    }
}

void FlapControlLogic_Task(void)
{
    CommandParser_Command_t command;
    FeedbackProcessor_Position_t feedback;

    FeedbackProcessor_Update();
    feedback = FeedbackProcessor_GetPosition();

    if (feedback.valid == false)
    {
        MotorDriver_StopMotor();
        LedStatusHandler_IndicateError();
        FlapControl_InMotion = false;
        FlapControl_State = FLAP_CONTROL_STATE_FAULT;
    }
    else
    {
        FlapControl_CurrentPosition = feedback.position;

        if (FlapControl_InMotion == true)
        {
            if (FlapControl_CurrentPosition == FlapControl_TargetPosition)
            {
                MotorDriver_StopMotor();
                LedStatusHandler_SetLedState(FlapControl_CurrentPosition);
                FlapControl_InMotion = false;
                FlapControl_State = FLAP_CONTROL_STATE_TARGET_REACHED;
            }
        }

        command = CommandParser_GetLatestCommand();
        if (command.valid == true)
        {
            FlapControlLogic_IssueMovementCmd(command.position);
            CommandParser_ClearLatestCommand();
        }
        else if (FlapControl_InMotion == false)
        {
            FlapControl_State = FLAP_CONTROL_STATE_IDLE;
        }
        else
        {
            /* Movement continues until feedback equivalence confirms target reached. */
        }
    }
}

FlapControl_State_t FlapControlLogic_GetState(void)
{
    return FlapControl_State;
}

bool FlapControlLogic_IsInMotion(void)
{
    return FlapControl_InMotion;
}
