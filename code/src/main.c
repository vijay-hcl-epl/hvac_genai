/**
 * @file main.c
 * @brief Application entry point – init + super-loop dispatcher.
 *
 * Traces: SWE-REQ-020 (startup), SWE-REQ-022 (constant monitoring),
 *         SWE-REQ-033 (responsiveness), SWE-REQ-034 (no assumed execution model)
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal super-loop
 */

#include "stm32f4xx_hal.h"
#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"

/**
 * @brief Application entry point.
 *
 * Performs system initialisation then enters an infinite super-loop
 * that continuously dispatches the command parser and flap control logic.
 * No RTOS constructs are used (SWE-REQ-026).
 */
int main(void)
{
    /* ---- System initialisation (SWE-REQ-020) ---- */
    SystemInit_Run();

    /* ---- Main task dispatcher – super-loop (SWE-REQ-022, SWE-REQ-033) ---- */
    while (1)
    {
        /* 1. Process any pending UART command (SWE-REQ-022) */
        CommandParser_Process();

        /* 2. Run flap control state machine (SWE-REQ-004, SWE-REQ-023) */
        FlapControl_Run();
    }

    /* Unreachable – required by MISRA for int main return */
    return 0;
}
