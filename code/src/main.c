/**
 * @file main.c
 * @brief Main application entry point – init and super-loop dispatcher.
 *
 * Calls SystemInit_App() for one-time initialisation, then runs
 * the main task dispatcher in a while(1) loop:
 *   1. Poll UART for commands (Command Parser)
 *   2. If new command, issue to Flap Control Logic
 *   3. Run Flap Control Logic (feedback, motor, LED management)
 *
 * Traces: SWE-REQ-020, SWE-REQ-022, SWE-REQ-033, SWE-REQ-034
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (bare-metal, no RTOS)
 */

#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"

/**
 * @brief Application entry point.
 * @return int  (never returns in embedded context)
 */
int main(void)
{
    /* One-time system initialisation [SWE-REQ-020] */
    SystemInit_App();

    /* Main super-loop [SWE-REQ-022, SWE-REQ-033] */
    while (1)
    {
        /* 1. Poll UART for new command [SWE-REQ-022] */
        CommandParser_Process();

        /* 2. Check for new validated command and forward to control logic */
        {
            CommandResult_t cmd = CommandParser_GetLatestCommand();
            if (cmd.valid == true)
            {
                /* Issue movement command [SWE-REQ-004, SWE-REQ-033] */
                FlapControlLogic_IssueMovementCmd(cmd.position);
            }
        }

        /* 3. Run flap control logic (feedback, motor, LED) [SWE-REQ-023, SWE-REQ-024] */
        FlapControlLogic_Run();
    }

    /* Never reached */
    return 0;
}
