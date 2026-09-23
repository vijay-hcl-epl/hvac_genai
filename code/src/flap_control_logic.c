/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation – movement decision and state management.
 *
 * Software Unit: Flap Control Logic
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---------- Static (file-scope) data [SWE-REQ-009, SWE-REQ-036] ---------- */

/** Current control state */
static FlapControlState_t s_State = FLAPCTRL_STATE_IDLE;

/** Last commanded target position (1..5), 0 = none */
static uint8_t s_TargetPosition = 0U;

/** Current feedback position cached for comparison */
static uint8_t s_CurrentPosition = 0U;

/** Flag: a new movement command has been issued */
static bool s_NewCommandPending = false;

/* ---------- Public API -------------------------------------------------- */

void FlapControlLogic_Init(void)
{
    s_State             = FLAPCTRL_STATE_IDLE;
    s_TargetPosition    = 0U;
    s_CurrentPosition   = 0U;
    s_NewCommandPending = false;
}

void FlapControlLogic_IssueMovementCmd(uint8_t target_pos)
{
    /* Store the target; actual evaluation done in Run() [SWE-REQ-004] */
    if ((target_pos >= 1U) && (target_pos <= 5U))
    {
        s_TargetPosition    = target_pos;
        s_NewCommandPending = true;
    }
}

void FlapControlLogic_Run(void)
{
    FeedbackResult_t fb;
    MotorDirection_t direction;

    /* Acquire latest feedback [SWE-REQ-023] */
    FeedbackProcessor_Update();
    fb = FeedbackProcessor_GetPosition();

    switch (s_State)
    {
        case FLAPCTRL_STATE_IDLE:
            if (s_NewCommandPending == true)
            {
                s_NewCommandPending = false;

                if (fb.valid == false)
                {
                    /* Feedback fault – go to FAULT [SWE-REQ-031] */
                    MotorDriver_Stop();
                    LedStatusHandler_IndicateError();
                    s_State = FLAPCTRL_STATE_FAULT;
                }
                else
                {
                    s_CurrentPosition = fb.position;

                    if (s_TargetPosition == s_CurrentPosition)
                    {
                        /* Already at target – ignore [SWE-REQ-006] */
                        LedStatusHandler_SetLedState(s_CurrentPosition);
                        s_State = FLAPCTRL_STATE_TARGET_REACHED;
                    }
                    else
                    {
                        /* Determine direction [SWE-REQ-004] */
                        if (s_TargetPosition > s_CurrentPosition)
                        {
                            direction = MOTOR_DIR_FORWARD;
                        }
                        else
                        {
                            direction = MOTOR_DIR_REVERSE;
                        }
                        MotorDriver_Drive(direction, true);
                        s_State = FLAPCTRL_STATE_MOVING;
                    }
                }
            }
            break;

        case FLAPCTRL_STATE_MOVING:
            if (fb.valid == false)
            {
                /* Feedback error during movement – stop motor [SWE-REQ-008, SWE-REQ-031] */
                MotorDriver_Stop();
                LedStatusHandler_IndicateError();
                s_State = FLAPCTRL_STATE_FAULT;
            }
            else
            {
                s_CurrentPosition = fb.position;

                if (s_CurrentPosition == s_TargetPosition)
                {
                    /* Target reached [SWE-REQ-005, SWE-REQ-024] */
                    MotorDriver_Stop();
                    LedStatusHandler_SetLedState(s_CurrentPosition);
                    s_State = FLAPCTRL_STATE_TARGET_REACHED;
                }
                else if (s_NewCommandPending == true)
                {
                    /* New command arrived while moving – re-evaluate */
                    s_NewCommandPending = false;

                    if (s_TargetPosition == s_CurrentPosition)
                    {
                        MotorDriver_Stop();
                        LedStatusHandler_SetLedState(s_CurrentPosition);
                        s_State = FLAPCTRL_STATE_TARGET_REACHED;
                    }
                    else
                    {
                        /* Adjust direction if needed */
                        if (s_TargetPosition > s_CurrentPosition)
                        {
                            MotorDriver_Drive(MOTOR_DIR_FORWARD, true);
                        }
                        else
                        {
                            MotorDriver_Drive(MOTOR_DIR_REVERSE, true);
                        }
                        /* Remain in MOVING */
                    }
                }
                else
                {
                    /* Continue moving – no action needed */
                }
            }
            break;

        case FLAPCTRL_STATE_TARGET_REACHED:
            /* Return to IDLE, ready for next command [SWE-REQ-005] */
            s_State = FLAPCTRL_STATE_IDLE;
            break;

        case FLAPCTRL_STATE_FAULT:
            /* Attempt recovery: check feedback validity */
            if (fb.valid == true)
            {
                s_CurrentPosition = fb.position;
                LedStatusHandler_SetLedState(s_CurrentPosition);
                s_State = FLAPCTRL_STATE_IDLE;
            }
            else
            {
                /* Remain in FAULT – motor stays stopped [SWE-REQ-032] */
                MotorDriver_Stop();
            }
            break;

        default:
            /* Defensive: go to FAULT */
            MotorDriver_Stop();
            s_State = FLAPCTRL_STATE_FAULT;
            break;
    }
}

FlapControlState_t FlapControlLogic_GetState(void)
{
    return s_State;
}
