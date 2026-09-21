#include "Flap_Control_Logic.h"
#include "Feedback_Processor.h"
#include "LED_Status_Handler.h"
#include "Motor_Driver.h"

static FlapControl_StateType flap_state;
static uint8_t current_position;
static uint8_t target_position;
static uint8_t in_motion;

void FlapControl_Init(void)
{
    flap_state = FLAP_CONTROL_STATE_IDLE;
    current_position = 0U;
    target_position = 0U;
    in_motion = 0U;
}

void FlapControl_IssueMovementCmd(uint8_t target_pos)
{
    FeedbackProcessor_PositionType feedback;

    FeedbackProcessor_Update();
    feedback = FeedbackProcessor_GetPosition();

    if ((feedback.valid == 0U) || (target_pos > FEEDBACK_PROCESSOR_POSITION_MAX))
    {
        MotorDriver_StopMotor();
        LEDStatusHandler_IndicateError();
        flap_state = FLAP_CONTROL_STATE_FAULT;
        in_motion = 0U;
    }
    else
    {
        current_position = feedback.position;
        target_position = target_pos;

        if (target_position == current_position)
        {
            MotorDriver_StopMotor();
            LEDStatusHandler_SetLedState(current_position);
            flap_state = FLAP_CONTROL_STATE_TARGET_REACHED;
            in_motion = 0U;
        }
        else if (target_position > current_position)
        {
            MotorDriver_DriveMotor(MOTOR_DRIVER_DIR_FORWARD, 1U);
            flap_state = FLAP_CONTROL_STATE_MOVING;
            in_motion = 1U;
        }
        else
        {
            MotorDriver_DriveMotor(MOTOR_DRIVER_DIR_REVERSE, 1U);
            flap_state = FLAP_CONTROL_STATE_MOVING;
            in_motion = 1U;
        }
    }
}

void FlapControl_EvaluateFeedback(void)
{
    FeedbackProcessor_PositionType feedback;

    FeedbackProcessor_Update();
    feedback = FeedbackProcessor_GetPosition();

    if (feedback.valid == 0U)
    {
        MotorDriver_StopMotor();
        LEDStatusHandler_IndicateError();
        flap_state = FLAP_CONTROL_STATE_FAULT;
        in_motion = 0U;
    }
    else
    {
        current_position = feedback.position;
        if ((in_motion != 0U) && (current_position == target_position))
        {
            MotorDriver_StopMotor();
            LEDStatusHandler_SetLedState(current_position);
            flap_state = FLAP_CONTROL_STATE_TARGET_REACHED;
            in_motion = 0U;
        }
        else if (in_motion == 0U)
        {
            flap_state = FLAP_CONTROL_STATE_IDLE;
        }
        else
        {
            flap_state = FLAP_CONTROL_STATE_MOVING;
        }
    }
}

FlapControl_StateType FlapControl_GetState(void)
{
    return flap_state;
}

uint8_t FlapControl_GetTargetPosition(void)
{
    return target_position;
}
