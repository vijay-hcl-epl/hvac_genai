/**
 * @file system_init.c
 * @brief System Startup / Initialisation implementation.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021
 */

#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "led_status_handler.h"
#include "motor_driver.h"

/* ---- Public API ---- */

uint8_t SystemInit_Run(void)
{
    FbResult_t fbInit;

    /* ---- Initialise all software units [SWE-REQ-020] ---- */
    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControl_Init();
    MotorDriver_Init();
    LedStatus_Init();

    /* ---- Ensure motor is off [SWE-REQ-020] ---- */
    MotorDriver_Stop();

    /* ---- Power LED on [SWE-REQ-012] ---- */
    LedStatus_SetPowerLed();

    /* ---- Read initial feedback and indicate on LEDs [SWE-REQ-021] ---- */
    FeedbackProcessor_Update();
    fbInit = FeedbackProcessor_GetPosition();

    if (fbInit.valid == FB_VALID)
    {
        LedStatus_SetPosition(fbInit.position);
    }
    else
    {
        LedStatus_IndicateError();
    }

    return 0U; /* Success */
}
