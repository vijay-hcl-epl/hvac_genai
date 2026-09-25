/**
 * @file system_init.h
 * @brief System Startup / Initialisation – One-time peripheral and unit init.
 *
 * Traces: SWE-REQ-020
 * Platform: STM32F407G-DISC1 / STM32 HAL
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdint.h>

/**
 * @brief Perform full system initialisation.
 *        Configures HAL, clocks, and calls init for every software unit.
 *        Ensures motor is off and LEDs reflect initial state.
 */
void system_init(void);

#endif /* SYSTEM_INIT_H */
