/**
 * @file main.c
 * @brief Application entry point – HVAC Flap Actuator
 *
 * Calls system initialisation then enters the infinite main loop
 * that dispatches the Command Parser and Flap Control Logic tasks.
 *
 * Traceability:
 *   SWE-REQ-020 (init), SWE-REQ-022 (constant monitoring),
 *   SWE-REQ-033 (responsiveness), SWE-REQ-034 (no hard-coded exec model),
 *   SWE-REQ-026 (no OS/RTOS)
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"

/**
 * @brief Application entry point.
 * @return int  (never returns in bare-metal firmware)
 *
 * [SWE-REQ-020, SWE-REQ-022, SWE-REQ-033, SWE-REQ-026]
 */
int main(void)
{
    /* ---- STEP 1: Full system initialisation [SWE-REQ-020] ---- */
    SystemInit_Run();

    /* ---- STEP 2: Main infinite loop [SWE-REQ-022, SWE-REQ-033] ---- */
    while (1)
    {
        /* Process UART commands [SWE-REQ-022, SWE-REQ-001] */
        CommandParser_Process();

        /* Run flap control logic (reads cmd + feedback, drives motor + LEDs)
         * [SWE-REQ-004, SWE-REQ-023, SWE-REQ-024] */
        FlapControlLogic_Run();
    }

    /* Should never reach here in bare-metal [SWE-REQ-026] */
    return 0;
}
