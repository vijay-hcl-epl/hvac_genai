/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---- Module static data [SWE-REQ-009, SWE-REQ-036] ---- */
static FlapStatus_t s_flapStatus;

/* ---- Public API ---- */

void FlapControl_Init(void)
{
    s_flapStatus.state           = FLAP_STATE_IDLE;
    s_flapStatus.currentPosition = 0U;
    s_flapStatus.targetPosition  = 0U;
    s_flapStatus.inMotion        = 0U;
}

void FlapControl_SetTarget(uint8_t targetPos)
{
    /* Store commanded target [SWE-REQ-004] */
    s_flapStatus.targetPosition = targetPos;
}

void FlapControl_Run(void)
{
    FbResult_t fb;

    /* Acquire current feedback [SWE-REQ-023] */
    FeedbackProcessor_Update();
    fb = FeedbackProcessor_GetPosition();

    /* ---- Fault handling [SWE-REQ-031, SWE-REQ-025] ---- */
    if (fb.valid == FB_INVALID)
    {
        MotorDriver_Stop();
        s_flapStatus.state    = FLAP_STATE_FAULT;
        s_flapStatus.inMotion = 0U;
        LedStatus_IndicateError();
        return;
    }

    /* Update current position from feedback */
    s_flapStatus.currentPosition = fb.position;

    switch (s_flapStatus.state)
    {
        case FLAP_STATE_IDLE:
            /* Check if a new target differs from current [SWE-REQ-006] */
            if ((s_flapStatus.targetPosition != 0U) &&
                (s_flapStatus.targetPosition != s_flapStatus.currentPosition))
            {
                /* Determine direction [SWE-REQ-004] */
                if (s_flapStatus.targetPosition > s_flapStatus.currentPosition)
                {
                    MotorDriver_Drive(MOTOR_DIR_FORWARD, 1U);
                }
                else
                {
                    MotorDriver_Drive(MOTOR_DIR_REVERSE, 1U);
                }
                s_flapStatus.state    = FLAP_STATE_MOVING;
                s_flapStatus.inMotion = 1U;
            }
            else
            {
                /* Target equals current or no command → no action [SWE-REQ-006] */
                LedStatus_SetPosition(s_flapStatus.currentPosition);
            }
            break;

        case FLAP_STATE_MOVING:
            /* Check if target reached [SWE-REQ-005, SWE-REQ-024] */
            if (s_flapStatus.currentPosition == s_flapStatus.targetPosition)
            {
                MotorDriver_Stop();
                s_flapStatus.state    = FLAP_STATE_TARGET_REACHED;
                s_flapStatus.inMotion = 0U;
                LedStatus_SetPosition(s_flapStatus.currentPosition);
            }
            else
            {
                /* Still moving – re-evaluate direction in case of overshoot */
                if (s_flapStatus.targetPosition > s_flapStatus.currentPosition)
                {
                    MotorDriver_Drive(MOTOR_DIR_FORWARD, 1U);
                }
                else
                {
                    MotorDriver_Drive(MOTOR_DIR_REVERSE, 1U);
                }
            }
            break;

        case FLAP_STATE_TARGET_REACHED:
            /* Transition back to idle, ready for next command */
            s_flapStatus.state = FLAP_STATE_IDLE;
            break;

        case FLAP_STATE_FAULT:
            /* Attempt recovery: if feedback becomes valid again */
            if (fb.valid == FB_VALID)
            {
                s_flapStatus.state = FLAP_STATE_IDLE;
                LedStatus_SetPosition(s_flapStatus.currentPosition);
            }
            else
            {
                MotorDriver_Stop();
                LedStatus_IndicateError();
            }
            break;

        default:
            /* Defensive: go to idle */
            s_flapStatus.state = FLAP_STATE_IDLE;
            break;
    }
}

FlapStatus_t FlapControl_GetStatus(void)
{
    return s_flapStatus;
}
