/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and unit init.
 *
 * Software Unit: System Startup/Initialization
 * Traces: SWE-REQ-020
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/**
 * @brief Perform one-time system initialisation.
 *        Initialises HAL, clocks, all software units, reads initial
 *        feedback, sets LEDs, and ensures motor is off.
 *        [SWE-REQ-020, SWE-REQ-021]
 */
void SystemInit_App(void);

#endif /* SYSTEM_INIT_H */
