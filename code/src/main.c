/**
 * @file main.c
 * @brief Application entry point – init + main dispatcher loop.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021, SWE-REQ-022, SWE-REQ-033, SWE-REQ-034
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include <stdint.h>
#include <stdbool.h>
#include "system_init.h"
#include "flap_control_logic.h"
#include "led_status_handler.h"

/**
 * @brief Application entry point.
 *
 * Calls SystemInit_Run() once, then enters an infinite main-loop
 * that dispatches FlapControl_Run() cyclically (SWE-REQ-033, SWE-REQ-034).
 *
 * @return int  Never returns in bare-metal.
 */
int main(void)
{
    bool init_ok;

    /* ---- STEP 1: Full system initialisation (SWE-REQ-020) ---- */
    init_ok = SystemInit_Run();

    if (!init_ok)
    {
        /* Indicate initialisation failure and halt safely. */
        LedStatus_IndicateError();
        while (1)
        {
            /* Safe halt – no motor activity, error indicated. */
        }
    }

    /* ---- STEP 2: Main task dispatcher loop (SWE-REQ-022, SWE-REQ-033) ---- */
    while (1)
    {
        FlapControl_Run();
    }

    /* Never reached in bare-metal; return for MISRA compliance. */
    return 0;
}
