/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation – movement decision & state.
 *
 * Software Unit : Flap Control Logic
 * Traceability  : SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *                 SWE-REQ-024, SWE-REQ-031
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"
#include "command_parser.h"

/* ── Module-scope static data (SWE-REQ-009, SWE-REQ-036) ───────────── */
static uint8_t          s_current_pos   = 0U;
static uint8_t          s_target_pos    = 0U;
static uint8_t          s_in_motion     = 0U;
static FlapCtrl_State_t s_state         = FLAPCTRL_STATE_IDLE;

/* ── Public API ──────────────────────────────────────────────────────── */

void FlapCtrl_Init(void)
{
    s_current_pos = 0U;
    s_target_pos  = 0U;
    s_in_motion   = 0U;
    s_state       = FLAPCTRL_STATE_IDLE;
}

void FlapCtrl_IssueMovementCmd(uint8_t target_pos)
{
    /* SWE-REQ-006: ignore if target == current. */
    if (target_pos == s_current_pos)
    {
        /* No action required. */
        return;
    }

    s_target_pos = target_pos;

    /* SWE-REQ-004: initiate movement toward commanded position.         */
    if (s_state != FLAPCTRL_STATE_FAULT)
    {
        s_in_motion = 1U;
        s_state     = FLAPCTRL_STATE_MOVING;
    }
}

void FlapCtrl_Run(void)
{
    FbProc_Result_t fb;
    MotorDir_t      dir;

    /* ── 1. Check for new user command ─────────────────────────────── */
    {
        CmdParser_Result_t cmd;
        CmdParser_GetLatestCommand(&cmd);

        if (cmd.valid != 0U)
        {
            FlapCtrl_IssueMovementCmd(cmd.position);
            CmdParser_ClearCommand();
        }
    }

    /* ── 2. Acquire current feedback ───────────────────────────────── */
    FbProc_Update();
    FbProc_GetPosition(&fb);

    /* ── 3. Fault handling (SWE-REQ-031, SWE-REQ-025) ─────────────── */
    if (fb.valid == 0U)
    {
        MotorDrv_Stop();
        s_in_motion = 0U;
        s_state     = FLAPCTRL_STATE_FAULT;
        LedStatus_IndicateError();
        return;
    }

    s_current_pos = fb.position;

    /* ── 4. Movement state machine ─────────────────────────────────── */
    switch (s_state)
    {
        case FLAPCTRL_STATE_IDLE:
            /* Nothing to do – waiting for command. */
            break;

        case FLAPCTRL_STATE_MOVING:
            /* SWE-REQ-024: check if target reached. */
            if (s_current_pos == s_target_pos)
            {
                /* SWE-REQ-005: cease motor on target reached. */
                MotorDrv_Stop();
                s_in_motion = 0U;
                s_state     = FLAPCTRL_STATE_TARGET_REACHED;
                LedStatus_SetPosition(s_current_pos);
            }
            else
            {
                /* Determine direction. */
                if (s_target_pos > s_current_pos)
                {
                    dir = MOTOR_DIR_FORWARD;
                }
                else
                {
                    dir = MOTOR_DIR_REVERSE;
                }
                MotorDrv_Drive(dir, 1U);
            }
            break;

        case FLAPCTRL_STATE_TARGET_REACHED:
            /* SWE-REQ-005: motor already stopped; transition to IDLE. */
            s_state = FLAPCTRL_STATE_IDLE;
            break;

        case FLAPCTRL_STATE_FAULT:
            /* SWE-REQ-032: motor stopped, remain in fault until
             * feedback recovers (recovery = valid feedback). */
            if (fb.valid != 0U)
            {
                s_state = FLAPCTRL_STATE_IDLE;
                s_in_motion = 0U;
                LedStatus_SetPosition(fb.position);
            }
            break;

        default:
            /* Defensive: should not reach here. */
            MotorDrv_Stop();
            s_state = FLAPCTRL_STATE_FAULT;
            break;
    }
}

FlapCtrl_State_t FlapCtrl_GetState(void)
{
    return s_state;
}
