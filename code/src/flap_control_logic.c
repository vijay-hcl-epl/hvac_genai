/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation – movement decision engine.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *         SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---- Private data ----------------------------------------------------- */

/** Static control state (SWE-REQ-009, SWE-REQ-036). */
static FlapState_t s_flap_state;
static uint8_t     s_target_position;
static uint8_t     s_current_position;

/* ---- Public API ------------------------------------------------------- */

void FlapControl_Init(void)
{
    s_flap_state      = FLAP_STATE_IDLE;
    s_target_position  = 0U;
    s_current_position = 0U;
}

void FlapControl_Run(void)
{
    uint8_t cmd_pos   = 0U;
    bool    cmd_valid = false;
    uint8_t fb_pos    = 0U;
    bool    fb_valid  = false;

    /* --- 1. Acquire feedback (SWE-REQ-023) --- */
    FeedbackProcessor_Update();
    FeedbackProcessor_GetPosition(&fb_pos, &fb_valid);

    if (!fb_valid)
    {
        /* Feedback fault – enter FAULT, stop motor (SWE-REQ-008, SWE-REQ-025, SWE-REQ-031). */
        MotorDriver_Stop();
        s_flap_state = FLAP_STATE_FAULT;
        LedStatus_IndicateError();
        return;
    }

    s_current_position = fb_pos;

    /* --- 2. Check for new user command (SWE-REQ-022) --- */
    CommandParser_Process();
    CommandParser_GetLatestCommand(&cmd_pos, &cmd_valid);

    if (cmd_valid)
    {
        /* Consume command. */
        CommandParser_ClearCommand();

        /* If target == current, ignore (SWE-REQ-006). */
        if (cmd_pos != s_current_position)
        {
            s_target_position = cmd_pos;
            s_flap_state      = FLAP_STATE_MOVING;
        }
    }

    /* --- 3. State-dependent action --- */
    switch (s_flap_state)
    {
        case FLAP_STATE_IDLE:
            /* Nothing to do – motor already off. */
            break;

        case FLAP_STATE_MOVING:
        {
            /* Check if target reached (SWE-REQ-005, SWE-REQ-024). */
            if (s_current_position == s_target_position)
            {
                MotorDriver_Stop();
                s_flap_state = FLAP_STATE_TARGET_REACHED;
                LedStatus_SetPosition(s_current_position);
            }
            else
            {
                /* Determine direction and drive (SWE-REQ-004, SWE-REQ-007). */
                if (s_target_position > s_current_position)
                {
                    MotorDriver_Drive(MOTOR_DIR_FORWARD, true);
                }
                else
                {
                    MotorDriver_Drive(MOTOR_DIR_REVERSE, true);
                }
            }
            break;
        }

        case FLAP_STATE_TARGET_REACHED:
            /* Transition back to IDLE after indicating. */
            s_flap_state = FLAP_STATE_IDLE;
            break;

        case FLAP_STATE_FAULT:
            /* Recovery: if feedback becomes valid again, go IDLE. */
            if (fb_valid)
            {
                MotorDriver_Stop();
                s_flap_state = FLAP_STATE_IDLE;
                LedStatus_SetPosition(s_current_position);
            }
            break;

        default:
            /* Defensive: force safe state. */
            MotorDriver_Stop();
            s_flap_state = FLAP_STATE_IDLE;
            break;
    }
}

FlapState_t FlapControl_GetState(void)
{
    return s_flap_state;
}
