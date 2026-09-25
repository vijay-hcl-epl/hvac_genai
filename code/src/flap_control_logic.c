/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation – state machine, movement decisions.
 *
 * Traces: SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031
 * Platform: STM32F407G-DISC1
 */

#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---- Internal state (static) [SWE-REQ-009, SWE-REQ-036] ---- */
static flap_state_t  s_state;
static uint8_t       s_target_position;
static uint8_t       s_current_position;

/* ---- Public API ---- */

void flap_control_init(void)
{
    s_state            = FLAP_STATE_IDLE;
    s_target_position  = 0U;
    s_current_position = 0U;
}

void flap_control_set_target(uint8_t target_pos)
{
    s_target_position = target_pos;
}

void flap_control_update(void)
{
    uint8_t new_cmd    = 0U;
    uint8_t fb_pos     = 0U;
    uint8_t fb_valid   = 0U;

    /* --- Read latest command [SWE-REQ-022, SWE-REQ-023] --- */
    if (command_parser_get_latest(&new_cmd) != 0U)
    {
        s_target_position = new_cmd;
    }

    /* --- Read feedback [SWE-REQ-010] --- */
    fb_valid = feedback_processor_get_position(&fb_pos);

    /* --- State machine --- */
    switch (s_state)
    {
        case FLAP_STATE_IDLE:
            if ((s_target_position != 0U) && (fb_valid != 0U))
            {
                if (s_target_position != fb_pos)
                {
                    /* Need to move [SWE-REQ-004] */
                    if (s_target_position > fb_pos)
                    {
                        motor_driver_drive(MOTOR_DIR_FORWARD, 1U);
                    }
                    else
                    {
                        motor_driver_drive(MOTOR_DIR_REVERSE, 1U);
                    }
                    s_state = FLAP_STATE_MOVING;
                }
                else
                {
                    /* Target equals current – ignore [SWE-REQ-006] */
                    s_state = FLAP_STATE_TARGET_REACHED;
                }
            }
            else if (fb_valid == 0U)
            {
                /* Feedback fault – enter fault [SWE-REQ-031] */
                motor_driver_stop();
                led_status_indicate_error();
                s_state = FLAP_STATE_FAULT;
            }
            else
            {
                /* No target yet – remain idle */
            }
            break;

        case FLAP_STATE_MOVING:
            if (fb_valid == 0U)
            {
                /* Feedback error during movement – emergency stop [SWE-REQ-008, SWE-REQ-025] */
                motor_driver_stop();
                led_status_indicate_error();
                s_state = FLAP_STATE_FAULT;
            }
            else if (fb_pos == s_target_position)
            {
                /* Target reached [SWE-REQ-005, SWE-REQ-024] */
                motor_driver_stop();
                s_current_position = fb_pos;
                led_status_set_position(s_current_position);
                s_state = FLAP_STATE_TARGET_REACHED;
            }
            else
            {
                /* Still moving – re-evaluate direction in case of overshoot */
                if (s_target_position > fb_pos)
                {
                    motor_driver_drive(MOTOR_DIR_FORWARD, 1U);
                }
                else
                {
                    motor_driver_drive(MOTOR_DIR_REVERSE, 1U);
                }
            }
            break;

        case FLAP_STATE_TARGET_REACHED:
            /* Update LEDs for current position [SWE-REQ-013, SWE-REQ-014] */
            s_current_position = fb_pos;
            led_status_set_position(s_current_position);
            s_state = FLAP_STATE_IDLE;
            break;

        case FLAP_STATE_FAULT:
            /* Remain in fault until feedback recovers */
            motor_driver_stop();
            if (fb_valid != 0U)
            {
                /* Recovery – return to idle */
                s_current_position = fb_pos;
                led_status_set_position(s_current_position);
                s_state = FLAP_STATE_IDLE;
            }
            break;

        default:
            /* Defensive: unknown state – go to fault */
            motor_driver_stop();
            s_state = FLAP_STATE_FAULT;
            break;
    }
}

flap_state_t flap_control_get_state(void)
{
    return s_state;
}
