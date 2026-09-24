/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---------- Static data (SWE-REQ-009, SWE-REQ-036) ---------- */

static FlapState_t g_state           = FLAP_STATE_IDLE;
static uint8_t     g_target_position = 0U;
static uint8_t     g_current_position = 0U;

/* ---------- Public API ---------- */

void FlapControl_Init(void)
{
    g_state            = FLAP_STATE_IDLE;
    g_target_position  = 0U;
    g_current_position = 0U;
}

void FlapControl_SetTarget(uint8_t target_pos)
{
    uint8_t fb_pos   = 0U;
    uint8_t fb_valid = 0U;

    /* SWE-REQ-006: ignore if target equals current feedback position */
    FeedbackProcessor_GetPosition(&fb_pos, &fb_valid);

    if (fb_valid == FB_INVALID)
    {
        /* Feedback fault – enter FAULT, stop motor (SWE-REQ-031, SWE-REQ-025) */
        MotorDriver_Stop();
        LedStatus_IndicateError();
        g_state = FLAP_STATE_FAULT;
        return;
    }

    if (target_pos == fb_pos)
    {
        /* Already at target – no action (SWE-REQ-006) */
        g_state = FLAP_STATE_TARGET_REACHED;
        return;
    }

    g_target_position = target_pos;
    g_current_position = fb_pos;

    /* Determine direction and start motor (SWE-REQ-004, SWE-REQ-007) */
    if (target_pos > fb_pos)
    {
        MotorDriver_Drive(MOTOR_DIR_FORWARD, MOTOR_ENABLE);
    }
    else
    {
        MotorDriver_Drive(MOTOR_DIR_REVERSE, MOTOR_ENABLE);
    }

    g_state = FLAP_STATE_MOVING;
}

void FlapControl_Run(void)
{
    uint8_t fb_pos   = 0U;
    uint8_t fb_valid = 0U;

    if (g_state == FLAP_STATE_IDLE)
    {
        return; /* Nothing to do */
    }

    if (g_state == FLAP_STATE_TARGET_REACHED)
    {
        return; /* Stable – wait for new command */
    }

    /* Update feedback (SWE-REQ-023) */
    FeedbackProcessor_Update();
    FeedbackProcessor_GetPosition(&fb_pos, &fb_valid);

    /* SWE-REQ-031, SWE-REQ-025: fault handling */
    if (fb_valid == FB_INVALID)
    {
        MotorDriver_Stop();
        LedStatus_IndicateError();
        g_state = FLAP_STATE_FAULT;
        return;
    }

    g_current_position = fb_pos;

    /* SWE-REQ-024: check if target reached */
    if (fb_pos == g_target_position)
    {
        /* SWE-REQ-005, SWE-REQ-008: cease motor actuation */
        MotorDriver_Stop();
        /* SWE-REQ-013, SWE-REQ-014: update LED to new position */
        LedStatus_SetPosition(fb_pos);
        g_state = FLAP_STATE_TARGET_REACHED;
        return;
    }

    /* Still moving – adjust direction if needed */
    if (g_target_position > fb_pos)
    {
        MotorDriver_Drive(MOTOR_DIR_FORWARD, MOTOR_ENABLE);
    }
    else
    {
        MotorDriver_Drive(MOTOR_DIR_REVERSE, MOTOR_ENABLE);
    }

    /* SWE-REQ-032: check motor fault */
    if (MotorDriver_GetStatus() == MOTOR_STATUS_FAULT)
    {
        MotorDriver_Stop();
        LedStatus_IndicateError();
        g_state = FLAP_STATE_FAULT;
    }
}

FlapState_t FlapControl_GetState(void)
{
    return g_state;
}
