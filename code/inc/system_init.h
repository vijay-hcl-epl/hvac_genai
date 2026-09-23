/**
 * @file system_init.h
 * @brief System Startup / Initialisation Software Unit – Header
 *
 * One-time peripheral and variable initialisation, triggers safe
 * states on all outputs, reads initial feedback, and sets LEDs.
 *
 * Traceability:
 *   SWE-REQ-020
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/**
 * @brief Perform full system initialisation.
 *
 * Sequence:
 *   1. HAL_Init() and SystemClock_Config()
 *   2. Peripheral GPIO / UART / ADC / Timer-PWM init
 *   3. Initialise every software unit (Motor, Feedback, Command, LED, FlapControl)
 *   4. Ensure motor is OFF (safe state)
 *   5. Read initial feedback and indicate on LEDs
 *
 * [SWE-REQ-020, SWE-REQ-021]
 */
void SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
