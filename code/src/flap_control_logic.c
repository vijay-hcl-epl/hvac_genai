/**
 * @file flap_control_logic.c
 * @brief Flap Control Logic implementation.
 *
 * Software Unit : Flap Control Logic
 * Traces        : SWE-REQ-004, SWE-REQ-005, SWE-REQ-006, SWE-REQ-023,
 *                 SWE-REQ-024, SWE-REQ-031
 * Platform      : STM32F407G-DISC1
 */

#include "flap_control_logic.h"
#include "command_parser.h"
#include "feedback_processor.h"
#include "motor_driver.h"
#include "led_status_handler.h"

/* ---------- Static data (SWE-REQ-009, SWE-REQ-036) --------------------- */
static FlapControlData_t flapData;

/* ---------- Public API ------------------------------------------------- */

void FlapControl_Init(void)
{
    flapData.currentPos = 0U;
    flapData.targetPos  = 0U;
    flapData.inMotion   = 0U;
    flapData.state      = FLAP_STATE_IDLE;
}

void FlapControl_Run(void)
{
    uint8_t newCmd;
    uint8_t cmdAvailable;
    uint8_t fbPos;
    uint8_t fbValid;

    /* ---- 1. Acquire latest feedback (SWE-REQ-023) ---- */
    FeedbackProcessor_Update();
    fbValid = FeedbackProcessor_GetPosition(&fbPos);

    /* ---- 2. Check for feedback fault (SWE-REQ-031, SWE-REQ-025) ---- */
    if (fbValid == 0U)
    {
        /* Fault path: stop motor, set fault state */
        MotorDriver_Stop();
        flapData.inMotion = 0U;
        flapData.state    = FLAP_STATE_FAULT;
        LedStatus_IndicateError();
        return;
    }

    /* Update known current position */
    flapData.currentPos = fbPos;

    /* ---- 3. Process new command if available (SWE-REQ-001) ---- */
    cmdAvailable = CommandParser_GetLatestCommand(&newCmd);
    if (cmdAvailable == 1U)
    {
        flapData.targetPos = newCmd;
    }

    /* ---- 4. State machine ---- */
    switch (flapData.state)
    {
        case FLAP_STATE_IDLE:
            /* Fall-through to evaluate if movement needed */
        case FLAP_STATE_TARGET_REACHED:
            if (flapData.targetPos != flapData.currentPos)  /* SWE-REQ-006 */
            {
                /* Determine direction (SWE-REQ-004) */
                if (flapData.targetPos > flapData.currentPos)
                {
                    MotorDriver_Drive(MOTOR_DIR_FORWARD, 1U);
                }
                else
                {
                    MotorDriver_Drive(MOTOR_DIR_REVERSE, 1U);
                }
                flapData.inMotion = 1U;
                flapData.state    = FLAP_STATE_MOVING;
            }
            else
            {
                /* Already at target – update LEDs (SWE-REQ-013) */
                LedStatus_SetPosition(flapData.currentPos);
            }
            break;

        case FLAP_STATE_MOVING:
            /* Check if target reached (SWE-REQ-005, SWE-REQ-024) */
            if (flapData.currentPos == flapData.targetPos)
            {
                MotorDriver_Stop();  /* SWE-REQ-008 */
                flapData.inMotion = 0U;
                flapData.state    = FLAP_STATE_TARGET_REACHED;
                LedStatus_SetPosition(flapData.currentPos);  /* SWE-REQ-013 */
            }
            else
            {
                /* Still moving – re-evaluate direction in case of new command */
                if (flapData.targetPos > flapData.currentPos)
                {
                    MotorDriver_Drive(MOTOR_DIR_FORWARD, 1U);
                }
                else
                {
                    MotorDriver_Drive(MOTOR_DIR_REVERSE, 1U);
                }
            }
            break;

        case FLAP_STATE_FAULT:
            /* Recovery: if feedback becomes valid again, return to idle */
            MotorDriver_Stop();
            flapData.inMotion = 0U;
            flapData.state    = FLAP_STATE_IDLE;
            LedStatus_SetPosition(flapData.currentPos);
            break;

        default:
            /* Defensive: stop motor */
            MotorDriver_Stop();
            flapData.inMotion = 0U;
            flapData.state    = FLAP_STATE_IDLE;
            break;
    }
}

FlapControlState_t FlapControl_GetState(void)
{
    return flapData.state;
}
