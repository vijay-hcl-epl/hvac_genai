/**
 * @file    flap_control_logic.c
 * @brief   Flap Control Logic software unit – implementation.
 *
 * Traceability:
 *   SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-008, SWE-REQ-023,
 *   SWE-REQ-024, SWE-REQ-025, SWE-REQ-031, SWE-REQ-032, SWE-REQ-033,
 *   SWE-REQ-036.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

/* ---- Includes ------------------------------------------------------- */
#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---- Static Data (SWE-REQ-009, SWE-REQ-036) ------------------------ */

/** @brief Current flap-control state. */
static FlapControlState_t s_flapState;

/** @brief Last commanded target position. */
static uint8_t s_targetPosition;

/** @brief Tracks whether a target has been set at least once. */
static bool s_targetValid;

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020] */
void FlapControl_Init(void)
{
    s_flapState     = FLAP_STATE_IDLE;
    s_targetPosition = 0U;
    s_targetValid    = false;
}

/* [SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023, SWE-REQ-024,
    SWE-REQ-025, SWE-REQ-031, SWE-REQ-032, SWE-REQ-033] */
void FlapControl_Run(void)
{
    uint8_t cmdPos     = 0U;
    uint8_t currentPos = 0U;
    bool    cmdAvail;
    bool    fbValid;

    /* ---- 1. Poll command parser for new command ---- */
    /* [SWE-REQ-022, SWE-REQ-001] */
    CommandParser_Process();

    /* ---- 2. Update feedback ---- */
    /* [SWE-REQ-010, SWE-REQ-017] */
    FeedbackProcessor_Update();

    /* ---- 3. Read latest command ---- */
    cmdAvail = CommandParser_GetLatestCommand(&cmdPos);

    /* ---- 4. Read current feedback position ---- */
    fbValid = FeedbackProcessor_GetPosition(&currentPos);

    /* ---- 5. State machine ---- */
    switch (s_flapState)
    {
        case FLAP_STATE_IDLE:
            /* Check for new valid command. [SWE-REQ-023] */
            if (cmdAvail == true)
            {
                CommandParser_ConsumeCommand();

                if (fbValid == false)
                {
                    /* Feedback invalid – enter FAULT. [SWE-REQ-031, SWE-REQ-025] */
                    MotorDriver_Stop();
                    LedStatus_IndicateError();
                    s_flapState = FLAP_STATE_FAULT;
                }
                else if (cmdPos == currentPos)
                {
                    /* Target equals current – ignore. [SWE-REQ-006] */
                    LedStatus_SetPosition(currentPos);
                    s_flapState = FLAP_STATE_TARGET_REACHED;
                }
                else
                {
                    /* Need to move. [SWE-REQ-004, SWE-REQ-033] */
                    s_targetPosition = cmdPos;
                    s_targetValid    = true;

                    if (cmdPos > currentPos)
                    {
                        MotorDriver_Drive(MOTOR_DIR_CW, true);
                    }
                    else
                    {
                        MotorDriver_Drive(MOTOR_DIR_CCW, true);
                    }
                    s_flapState = FLAP_STATE_MOVING;
                }
            }
            break;

        case FLAP_STATE_MOVING:
            /* Continuous feedback check during motion. */
            if (fbValid == false)
            {
                /* Feedback fault – emergency stop. [SWE-REQ-008, SWE-REQ-025] */
                MotorDriver_Stop();
                LedStatus_IndicateError();
                s_flapState = FLAP_STATE_FAULT;
            }
            else if (currentPos == s_targetPosition)
            {
                /* Target reached. [SWE-REQ-005, SWE-REQ-024] */
                MotorDriver_Stop();
                LedStatus_SetPosition(currentPos);
                s_flapState = FLAP_STATE_TARGET_REACHED;
            }
            else
            {
                /* Still moving – check if a newer command arrived. */
                if (cmdAvail == true)
                {
                    CommandParser_ConsumeCommand();
                    s_targetPosition = cmdPos;
                    s_targetValid    = true;

                    /* Adjust direction if needed. */
                    if (cmdPos > currentPos)
                    {
                        MotorDriver_Drive(MOTOR_DIR_CW, true);
                    }
                    else if (cmdPos < currentPos)
                    {
                        MotorDriver_Drive(MOTOR_DIR_CCW, true);
                    }
                    else
                    {
                        /* New command matches current – stop. [SWE-REQ-006] */
                        MotorDriver_Stop();
                        LedStatus_SetPosition(currentPos);
                        s_flapState = FLAP_STATE_TARGET_REACHED;
                    }
                }
                /* Otherwise keep moving in current direction. */
            }
            break;

        case FLAP_STATE_TARGET_REACHED:
            /* Remain idle; accept new commands. [SWE-REQ-005] */
            if (cmdAvail == true)
            {
                CommandParser_ConsumeCommand();

                if (fbValid == false)
                {
                    MotorDriver_Stop();
                    LedStatus_IndicateError();
                    s_flapState = FLAP_STATE_FAULT;
                }
                else if (cmdPos != currentPos)
                {
                    s_targetPosition = cmdPos;
                    s_targetValid    = true;

                    if (cmdPos > currentPos)
                    {
                        MotorDriver_Drive(MOTOR_DIR_CW, true);
                    }
                    else
                    {
                        MotorDriver_Drive(MOTOR_DIR_CCW, true);
                    }
                    s_flapState = FLAP_STATE_MOVING;
                }
                /* else target == current: stay in TARGET_REACHED. [SWE-REQ-006] */
            }
            break;

        case FLAP_STATE_FAULT:
            /* Safe idle – motor stopped.  Attempt recovery on valid feedback.
               [SWE-REQ-032] */
            MotorDriver_Stop();
            if (fbValid == true)
            {
                /* Recovery – return to IDLE. */
                LedStatus_SetPosition(currentPos);
                s_flapState = FLAP_STATE_IDLE;
            }
            /* Consume any pending command to avoid stale data. */
            if (cmdAvail == true)
            {
                CommandParser_ConsumeCommand();
            }
            break;

        default:
            /* Defensive: should not reach here. Force safe state. */
            MotorDriver_Stop();
            s_flapState = FLAP_STATE_FAULT;
            break;
    }
}

/* [SWE-REQ-040] */
FlapControlState_t FlapControl_GetState(void)
{
    return s_flapState;
}
