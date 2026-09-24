/**
 * @file main.c
 * @brief Application entry point – init and main task dispatcher.
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal (no RTOS).
 *
 * Traces: SWE-REQ-020, SWE-REQ-022, SWE-REQ-023, SWE-REQ-033, SWE-REQ-034
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"

#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "led_status_handler.h"
#include "motor_driver.h"

/* ---------- UART handle (extern, defined in system_init.c) ---------- */
extern UART_HandleTypeDef huart2;

/* ---------- Static UART receive buffer (SWE-REQ-038) ---------- */
static uint8_t g_uart_rx_byte = 0U;

/**
 * @brief Main task dispatcher – polls UART, processes commands, runs control loop.
 *
 * Called repeatedly from the super-loop.
 *
 * Traces: SWE-REQ-022, SWE-REQ-023, SWE-REQ-033
 */
static void MainTask_Dispatch(void)
{
    uint8_t cmd_pos   = 0U;
    uint8_t cmd_valid = 0U;

    /* --- Poll UART for new command byte (SWE-REQ-022, SWE-REQ-015) --- */
    if (HAL_UART_Receive(&huart2, &g_uart_rx_byte, 1U, 1U) == HAL_OK)
    {
        CommandParser_ProcessByte(g_uart_rx_byte);
    }

    /* --- Check for a new validated command (SWE-REQ-001) --- */
    CommandParser_GetLatestCommand(&cmd_pos, &cmd_valid);

    if (cmd_valid != 0U)
    {
        /* SWE-REQ-004, SWE-REQ-006: issue target to flap control */
        FlapControl_SetTarget(cmd_pos);
    }

    /* --- Run flap control state machine (SWE-REQ-023, SWE-REQ-024, SWE-REQ-005) --- */
    FlapControl_Run();
}

/**
 * @brief Application entry point.
 *
 * Performs full system initialisation then enters infinite dispatch loop.
 *
 * @return int  Never returns.
 *
 * Traces: SWE-REQ-020, SWE-REQ-034
 */
int main(void)
{
    /* STEP 1: Full system initialisation (SWE-REQ-020) */
    SystemInit_Run();

    /* STEP 2: Super-loop – main task dispatcher (SWE-REQ-022, SWE-REQ-033) */
    while (1)
    {
        MainTask_Dispatch();
    }

    /* Never reached */
    return 0;
}
