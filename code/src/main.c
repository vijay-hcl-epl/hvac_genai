/**
 * @file main.c
 * @brief Application entry point – init + super-loop task dispatcher.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021, SWE-REQ-022, SWE-REQ-023, SWE-REQ-033, SWE-REQ-034
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL / Bare-metal (no RTOS)
 * Execution model: simple while(1) super-loop per SWE-REQ-026 / SWE-REQ-034.
 *
 * The super-loop:
 *   1. Checks for a new UART byte (non-blocking).
 *   2. If a valid command is available, issues it to Flap Control.
 *   3. Runs the Flap Control periodic task (feedback check, state machine).
 *
 * No dynamic allocation.  No RTOS constructs.
 */

#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL UART handle (initialised in system_init.c) ---- */
extern UART_HandleTypeDef huart2;

/* ---- Static UART receive buffer [SWE-REQ-038] ---- */
static uint8_t s_uart_rx_byte = 0U;

/**
 * @brief Application entry point.
 *
 * Performs full system initialisation then enters the main dispatcher loop.
 */
int main(void)
{
    HAL_StatusTypeDef uart_status;
    uint8_t cmd_position = 0U;

    /* ---- STEP 1: System initialisation [SWE-REQ-020, SWE-REQ-021] ---- */
    system_init();

    /* ---- STEP 2: Main super-loop [SWE-REQ-022, SWE-REQ-034] ---- */
    while (1)
    {
        /*
         * 2a. Poll UART for a new byte (non-blocking, 0 ms timeout).
         * SWE-REQ-015, SWE-REQ-022
         */
        uart_status = HAL_UART_Receive(&huart2, &s_uart_rx_byte, 1U, 0U);
        if (uart_status == HAL_OK)
        {
            /* Feed byte to Command Parser [SWE-REQ-001] */
            command_parser_process_byte(s_uart_rx_byte);
        }

        /*
         * 2b. If a new valid command is ready, issue it.
         * SWE-REQ-003, SWE-REQ-004, SWE-REQ-023, SWE-REQ-033
         */
        if (command_parser_get_latest(&cmd_position))
        {
            flap_control_issue_command(cmd_position);
        }

        /*
         * 2c. Run Flap Control periodic task (feedback, state transitions).
         * SWE-REQ-005, SWE-REQ-008, SWE-REQ-023, SWE-REQ-024, SWE-REQ-025
         */
        flap_control_run();
    }

    /* Should never reach here – no return value needed in bare-metal. */
    /* return 0; */  /* MISRA: unreachable code omitted intentionally */
}
