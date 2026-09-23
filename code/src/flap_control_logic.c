/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *   SWE-REQ-024, SWE-REQ-031
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---------- Static module data (no dynamic allocation) ---------- */
/* [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] */

/** Current flap-control state machine state */
static FlapControlState_t s_state = FLAP_STATE_IDLE;

/** Last commanded target position (1..N, 0 = none) */
static uint8_t s_targetPosition = 0U;

/** Last known current (feedback) position */
static uint8_t s_currentPosition = 0U;

/** Previous position for change-detection on LEDs [SWE-REQ-014] */
static uint8_t s_prevIndicatedPosition = 0U;

/* ---------- Public API ---------- */

/**
 * @brief Initialise the Flap Control Logic unit.
 *        [SWE-REQ-020]
 */
void FlapControlLogic_Init(void)
{
    s_state                = FLAP_STATE_IDLE;
    s_targetPosition       = 0U;
    s_currentPosition      = 0U;
    s_prevIndicatedPosition = 0U;
}

/**
 * @brief Main task dispatcher for flap control.
 *
 * Algorithm (per LLD):
 *   1. Read latest command from Command Parser.
 *   2. Read latest feedback from Feedback Processor.
 *   3. If feedback invalid → FAULT, stop motor, indicate error.
 *   4. If new valid command and target != current → MOVING, drive motor.
 *   5. If target == current → TARGET_REACHED / IDLE, stop motor.
 *   6. Update LED only on position change event.
 *
 * [SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024, SWE-REQ-031, SWE-REQ-033]
 */
void FlapControlLogic_Run(void)
{
    CommandResult_t  cmd;
    FeedbackResult_t fb;
    FlapDirection_t  dir;

    /* --- 1. Read command [SWE-REQ-023] --- */
    cmd = CommandParser_GetLatestCommand();

    /* --- 2. Read feedback [SWE-REQ-023, SWE-REQ-010] --- */
    FeedbackProcessor_Update();
    fb = FeedbackProcessor_GetPosition();

    /* --- 3. Feedback fault detection [SWE-REQ-031, SWE-REQ-025] --- */
    if (fb.valid == false)
    {
        /* Enter FAULT state – stop motor, indicate error [SWE-REQ-008, SWE-REQ-032] */
        MotorDriver_Stop();
        LedStatusHandler_IndicateError();
        s_state = FLAP_STATE_FAULT;
        return;
    }

    /* Update current position from feedback */
    s_currentPosition = fb.position;

    /* --- Update LED on position change [SWE-REQ-013, SWE-REQ-014, SWE-REQ-021] --- */
    if (s_currentPosition != s_prevIndicatedPosition)
    {
        LedStatusHandler_SetLedState(s_currentPosition);
        s_prevIndicatedPosition = s_currentPosition;
    }

    /* --- Recovery from FAULT if feedback now valid [LLD: FAULT→IDLE] --- */
    if (s_state == FLAP_STATE_FAULT)
    {
        s_state = FLAP_STATE_IDLE;
    }

    /* --- 4. Process new command [SWE-REQ-004, SWE-REQ-006] --- */
    if (cmd.valid == true)
    {
        s_targetPosition = cmd.position;
        CommandParser_ClearCommand();  /* consume command [SWE-REQ-003] */
    }

    /* --- 5. Decide on motor action --- */
    if (s_targetPosition == 0U)
    {
        /* No command received yet – stay idle */
        if (s_state == FLAP_STATE_MOVING)
        {
            MotorDriver_Stop();
        }
        s_state = FLAP_STATE_IDLE;
        return;
    }

    if (s_targetPosition == s_currentPosition)
    {
        /* Target reached [SWE-REQ-005, SWE-REQ-024] */
        if (s_state == FLAP_STATE_MOVING)
        {
            MotorDriver_Stop();   /* [SWE-REQ-008] */
        }
        s_state = FLAP_STATE_TARGET_REACHED;
        return;
    }

    /* Target differs from current – determine direction [SWE-REQ-004] */
    if (s_targetPosition > s_currentPosition)
    {
        dir = FLAP_DIR_FORWARD;
    }
    else
    {
        dir = FLAP_DIR_REVERSE;
    }

    /* Drive motor [SWE-REQ-007, SWE-REQ-033] */
    if (dir == FLAP_DIR_FORWARD)
    {
        MotorDriver_Drive(MOTOR_DIR_FORWARD, true);
    }
    else
    {
        MotorDriver_Drive(MOTOR_DIR_REVERSE, true);
    }
    s_state = FLAP_STATE_MOVING;
}

/**
 * @brief Retrieve the current state of the flap control state machine.
 */
FlapControlState_t FlapControlLogic_GetState(void)
{
    return s_state;
}
