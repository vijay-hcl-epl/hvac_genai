/**
 * @file    main.c
 * @brief   Application entry point – HVAC Flap Actuator firmware.
 *
 * Calls system initialisation, then enters the main super-loop
 * which dispatches the flap-control task cyclically.
 *
 * Traceability:
 *   SWE-REQ-020  – Initialise all device interfaces.
 *   SWE-REQ-022  – Constantly monitor for new UART commands.
 *   SWE-REQ-026  – No explicit OS / RTOS.
 *   SWE-REQ-034  – No hard-coded execution model constraints.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.  Bare-metal super-loop.
 */

/* ---- Includes ------------------------------------------------------- */
#include "stm32f4xx_hal.h"
#include "system_init.h"
#include "flap_control_logic.h"

/* ---- HAL Handle Definitions (used by all units via extern) ---------- */

/** @brief UART handle for command input (USART2). */
UART_HandleTypeDef huart2;

/** @brief ADC handle for potentiometer feedback (ADC1). */
ADC_HandleTypeDef hadc1;

/** @brief Timer handle for PWM motor enable (TIM3). */
TIM_HandleTypeDef htim3;

/* ---- Main ----------------------------------------------------------- */

/**
 * @brief  Application entry point.
 *         [SWE-REQ-020, SWE-REQ-022, SWE-REQ-026, SWE-REQ-034]
 * @return int  (never returns in embedded context).
 */
int main(void)
{
    /* ---- STEP 1: System Initialisation (SWE-REQ-020) ---- */
    SystemInit_Run();

    /* ---- STEP 2: Main Super-Loop (SWE-REQ-022, SWE-REQ-026) ---- */
    while (1)
    {
        /* Dispatch the main flap-control task.
         * This internally polls commands, reads feedback,
         * drives motor, and updates LEDs.
         * [SWE-REQ-004, SWE-REQ-023, SWE-REQ-033] */
        FlapControl_Run();
    }

    /* Should never reach here. */
    return 0;
}

/* ---- HAL Required Callbacks ----------------------------------------- */

/**
 * @brief  SysTick handler – required by STM32 HAL for timebase.
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}
