/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and module init.
 *
 * Traces: SWE-REQ-020
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/**
 * @brief Perform full system initialisation.
 *
 * Initialises HAL, system clocks, all peripheral drivers (UART, ADC, GPIO, PWM),
 * and all software units.  Reads initial feedback, sets power LED, and
 * indicates initial position on LEDs.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021
 */
void SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
