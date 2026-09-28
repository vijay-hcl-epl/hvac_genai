/**
 * @file main.c
 * @brief Application entry point – init + main task dispatcher while(1) loop.
 *
 * Traces: SWE-REQ-020, SWE-REQ-022, SWE-REQ-023, SWE-REQ-033, SWE-REQ-034
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#include <stdint.h>
#include "system_init.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "led_status_handler.h"
#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- UART handle (configured by SystemInit / CubeMX) ---- */
extern UART_HandleTypeDef huart2;

/**
 * @brief Main task dispatcher – called continuously in the super-loop.
 *
 * 1. Poll UART for incoming byte (SWE-REQ-022).
 * 2. If byte received, process via Command Parser.
 * 3. If valid command, issue to Flap Control Logic (SWE-REQ-023).
 * 4. Run one cycle of Flap Control Logic (SWE-REQ-004, SWE-REQ-033).
 *
 * Traces: SWE-REQ-022, SWE-REQ-023, SWE-REQ-033
 */
static void MainTask_Dispatch(void)
{
    uint8_t rx_byte = 0U;
    HAL_StatusTypeDef uart_status;
    CommandData_t cmd;

    /* 1. Poll UART for one byte (non-blocking) (SWE-REQ-022, SWE-REQ-015) */
    uart_status = HAL_UART_Receive(&huart2, &rx_byte, 1U, 1U);

    if (uart_status == HAL_OK)
    {
        /* 2. Process received byte (SWE-REQ-001) */
        CommandParser_ProcessByte(rx_byte);
    }

    /* 3. Check for valid command and issue to flap control (SWE-REQ-023) */
    cmd = CommandParser_GetLatestCommand();
    if (cmd.valid != 0U)
    {
        FlapControl_IssueMovementCmd(cmd.position);
    }

    /* 4. Run one control cycle (SWE-REQ-004, SWE-REQ-033) */
    FlapControl_Run();
}

/**
 * @brief Application entry point.
 *
 * Calls system init, then enters infinite super-loop calling the task dispatcher.
 *
 * Traces: SWE-REQ-020, SWE-REQ-034
 *
 * @return int  Never returns.
 */
int main(void)
{
    /* System initialisation (SWE-REQ-020) */
    SystemInit_Run();

    /* Read initial feedback and indicate on LEDs (SWE-REQ-021) */
    FeedbackProcessor_Update();
    {
        FeedbackData_t fb_init = FeedbackProcessor_GetPosition();
        if (fb_init.valid != 0U)
        {
            LedStatus_SetPositionLed(fb_init.position);
        }
    }

    /* Main super-loop (SWE-REQ-022, SWE-REQ-034) */
    while (1)
    {
        MainTask_Dispatch();
    }

    /* Never reached */
    return 0;
}
