/**
 * @file main.c
 * @brief Application entry point – init + main dispatcher loop.
 *
 * Trace: SWE-REQ-020, SWE-REQ-022, SWE-REQ-026, SWE-REQ-034
 *
 * This file provides the minimal execution glue required by SWE-REQ-026
 * (no explicit OS/RTOS/interrupt binding in the behavioural model) and
 * SWE-REQ-034 (no hard-coded execution-model constraints beyond stated
 * requirements).  The while(1) loop is the simplest compliant execution
 * model; it continuously monitors UART and dispatches control logic.
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal.
 *
 * CONFIGURATION GAP: UART handle (huart2) and its DMA/IT mode, baud rate
 * etc. are assumed placeholders configured in system_init.c.  A single
 * polling-based UART receive is used here for simplicity; a production
 * system may use interrupt-driven RX – that is a board-integration
 * decision, not a behavioural-model mandate.
 */

#include "stm32f4xx_hal.h"
#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"

/* ── External UART handle (configured in system_init.c) ─────────────── */
extern UART_HandleTypeDef huart2;

/* ── Static RX buffer (SWE-REQ-038) ─────────────────────────────────── */
static uint8_t s_rx_byte = 0U;

/**
 * @brief Application entry point.
 */
int main(void)
{
    /* ── STEP 1: Full system initialisation (SWE-REQ-020) ──────────── */
    System_Init();

    /* ── STEP 2: Main task dispatcher loop (SWE-REQ-022, SWE-REQ-034) ─ */
    while (1)
    {
        /* 2a. Monitor UART for new command byte (SWE-REQ-022).
         *     Non-blocking receive attempt; timeout = 1 ms.
         *     NOTE: Timeout value is a configurable responsiveness
         *     parameter (SWE-REQ-035).                                  */
        if (HAL_UART_Receive(&huart2, &s_rx_byte, 1U, 1U) == HAL_OK)
        {
            CmdParser_ProcessByte(s_rx_byte);
        }

        /* 2b. Run flap control logic (reads feedback, drives motor,
         *     updates LEDs as needed).                                  */
        FlapCtrl_Run();
    }

    /* Should never reach here in bare-metal. */
    return 0;
}
