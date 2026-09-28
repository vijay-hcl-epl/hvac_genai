/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation – movement decision state machine.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---- Internal static state (SWE-REQ-009, SWE-REQ-036) ---- */

static FlapState_t g_flap_state;
static uint8_t     g_target_position;
static uint8_t     g_current_position;
static uint8_t     g_command_pending;

/* ================================================================== */

void FlapControl_Init(void)
{
    g_flap_state       = FLAP_STATE_IDLE;
    g_target_position  = 0U;
    g_current_position = 0U;
    g_command_pending  = 0U;
}

/* ------------------------------------------------------------------ */

void FlapControl_IssueMovementCmd(uint8_t target_pos)
{
    /* Store target; will be processed in Run() (SWE-REQ-004, SWE-REQ-023) */
    g_target_position = target_pos;
    g_command_pending = 1U;
}

/* ------------------------------------------------------------------ */

void FlapControl_Run(void)
{
    FeedbackData_t fb;
    MotorDirection_t dir;

    /* Acquire latest feedback (SWE-REQ-023) */
    FeedbackProcessor_Update();
    fb = FeedbackProcessor_GetPosition();

    /* ---------- FAULT handling (SWE-REQ-031, SWE-REQ-025) ---------- */
    if (fb.valid == 0U)
    {
        MotorDriver_Stop();
        g_flap_state = FLAP_STATE_FAULT;
        LedStatus_IndicateError();
        return;
    }

    g_current_position = fb.position;

    /* ---------- State machine ---------- */
    switch (g_flap_state)
    {
        case FLAP_STATE_IDLE:
            /* Fall-through to check for new command */
            if (g_command_pending != 0U)
            {
                g_command_pending = 0U;

                /* SWE-REQ-006: ignore if target == current */
                if (g_target_position == g_current_position)
                {
                    /* Already at target – no movement */
                    g_flap_state = FLAP_STATE_TARGET_REACHED;
                    LedStatus_SetPositionLed(g_current_position);
                }
                else
                {
                    /* Determine direction (SWE-REQ-004) */
                    if (g_target_position > g_current_position)
                    {
                        dir = MOTOR_DIR_FORWARD;
                    }
                    else
                    {
                        dir = MOTOR_DIR_REVERSE;
                    }
                    MotorDriver_Drive(dir, 1U);
                    g_flap_state = FLAP_STATE_MOVING;
                }
            }
            break;

        case FLAP_STATE_MOVING:
            /* Check if target reached (SWE-REQ-005, SWE-REQ-024) */
            if (g_current_position == g_target_position)
            {
                MotorDriver_Stop();
                g_flap_state = FLAP_STATE_TARGET_REACHED;
                LedStatus_SetPositionLed(g_current_position);
            }
            /* Accept new command while moving (SWE-REQ-003 latest-wins) */
            else if (g_command_pending != 0U)
            {
                g_command_pending = 0U;
                if (g_target_position == g_current_position)
                {
                    MotorDriver_Stop();
                    g_flap_state = FLAP_STATE_TARGET_REACHED;
                    LedStatus_SetPositionLed(g_current_position);
                }
                else
                {
                    if (g_target_position > g_current_position)
                    {
                        dir = MOTOR_DIR_FORWARD;
                    }
                    else
                    {
                        dir = MOTOR_DIR_REVERSE;
                    }
                    MotorDriver_Drive(dir, 1U);
                    /* stay in MOVING */
                }
            }
            else
            {
                /* Continue moving – no action */
            }
            break;

        case FLAP_STATE_TARGET_REACHED:
            /* Transition back to IDLE, ready for next command */
            g_flap_state = FLAP_STATE_IDLE;
            break;

        case FLAP_STATE_FAULT:
            /* Attempt recovery: if feedback now valid, go IDLE (SWE-REQ-031) */
            MotorDriver_Stop();
            if (fb.valid != 0U)
            {
                g_flap_state = FLAP_STATE_IDLE;
                LedStatus_SetPositionLed(g_current_position);
            }
            break;

        default:
            /* Defensive: treat as fault */
            MotorDriver_Stop();
            g_flap_state = FLAP_STATE_FAULT;
            break;
    }
}

/* ------------------------------------------------------------------ */

FlapState_t FlapControl_GetState(void)
{
    return g_flap_state;
}
