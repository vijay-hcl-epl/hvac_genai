/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation.
 *
 * Software Unit: Flap Control Logic
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1 (logic layer – no direct HW access)
 * No dynamic allocation (SWE-REQ-036).  All state is static.
 */

#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

#include <stdbool.h>

/* ---- Module static state [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] ---- */

static flap_state_t s_state          = FLAP_STATE_IDLE;
static uint8_t      s_target_pos     = 0U;   /* 0 = no target yet */
static uint8_t      s_current_pos    = 0U;
static bool         s_has_target     = false;

/* ---- Public API ---- */

void flap_control_init(void)
{
    s_state       = FLAP_STATE_IDLE;
    s_target_pos  = 0U;
    s_current_pos = 0U;
    s_has_target  = false;
}

/*
 * SWE-REQ-004 : drive motor toward commanded position
 * SWE-REQ-006 : ignore if target == current
 * SWE-REQ-023 : compare command with feedback, move if needed
 * SWE-REQ-033 : initiate movement as soon as requirements satisfied
 */
void flap_control_issue_command(uint8_t target_pos)
{
    uint8_t fb_pos   = 0U;
    bool    fb_valid = false;

    feedback_processor_update();
    feedback_processor_get_position(&fb_pos, &fb_valid);

    if (!fb_valid)
    {
        /* Feedback fault – enter FAULT, stop motor [SWE-REQ-025, SWE-REQ-031] */
        motor_driver_stop();
        led_status_indicate_error();
        s_state = FLAP_STATE_FAULT;
        return;
    }

    s_current_pos = fb_pos;

    /* If target equals current position, ignore [SWE-REQ-006] */
    if (target_pos == s_current_pos)
    {
        motor_driver_stop();
        s_state = FLAP_STATE_TARGET_REACHED;
        led_status_set_position(s_current_pos);
        return;
    }

    /* Determine direction */
    s_target_pos = target_pos;
    s_has_target = true;

    if (s_target_pos > s_current_pos)
    {
        motor_driver_drive(MOTOR_DIR_FORWARD, 1U);
    }
    else
    {
        motor_driver_drive(MOTOR_DIR_REVERSE, 1U);
    }

    s_state = FLAP_STATE_MOVING;
}

/*
 * SWE-REQ-005 : cease actuation once target confirmed via feedback
 * SWE-REQ-008 : stop on invalid feedback or target reached
 * SWE-REQ-023 : compare command with feedback
 * SWE-REQ-024 : confirm target reached by position equivalence
 * SWE-REQ-025 : cease motor on error
 * SWE-REQ-031 : identify and handle out-of-range feedback
 */
void flap_control_run(void)
{
    uint8_t fb_pos   = 0U;
    bool    fb_valid = false;

    if (s_state == FLAP_STATE_IDLE || s_state == FLAP_STATE_TARGET_REACHED)
    {
        /* Nothing to do – waiting for a new command */
        return;
    }

    if (s_state == FLAP_STATE_FAULT)
    {
        /* Attempt recovery: re-read feedback */
        feedback_processor_update();
        feedback_processor_get_position(&fb_pos, &fb_valid);
        if (fb_valid)
        {
            s_state       = FLAP_STATE_IDLE;
            s_current_pos = fb_pos;
            led_status_set_position(fb_pos);
        }
        return;
    }

    /* FLAP_STATE_MOVING */
    feedback_processor_update();
    feedback_processor_get_position(&fb_pos, &fb_valid);

    if (!fb_valid)
    {
        /* Feedback fault while moving – safe stop [SWE-REQ-025, SWE-REQ-032] */
        motor_driver_stop();
        led_status_indicate_error();
        s_state = FLAP_STATE_FAULT;
        return;
    }

    s_current_pos = fb_pos;

    if (s_current_pos == s_target_pos)
    {
        /* Target reached [SWE-REQ-005, SWE-REQ-024] */
        motor_driver_stop();
        s_state = FLAP_STATE_TARGET_REACHED;
        s_has_target = false;
        led_status_set_position(s_current_pos);
    }
    else
    {
        /* Still moving – re-evaluate direction in case of overshoot */
        if (s_target_pos > s_current_pos)
        {
            motor_driver_drive(MOTOR_DIR_FORWARD, 1U);
        }
        else
        {
            motor_driver_drive(MOTOR_DIR_REVERSE, 1U);
        }
    }
}

flap_state_t flap_control_get_state(void)
{
    return s_state;
}
