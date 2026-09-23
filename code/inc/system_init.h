/**
 * @file    system_init.h
 * @brief   System Startup / Initialisation software unit – header.
 *
 * Performs one-time initialisation of all peripheral abstractions
 * (UART, GPIO, ADC, PWM/Timer, LEDs) and software units.
 * Ensures motor is OFF and initial state is indicated on LEDs.
 *
 * Traceability:
 *   SWE-REQ-020  – Initialise all device interfaces; motor OFF.
 *   SWE-REQ-021  – Read feedback and indicate initial state on LEDs.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  One-time system initialisation.
 *         Configures HAL, clocks, peripherals, then calls each
 *         software-unit Init function, reads initial feedback,
 *         sets power LED and initial position LED.
 *         [SWE-REQ-020, SWE-REQ-021]
 */
void SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
