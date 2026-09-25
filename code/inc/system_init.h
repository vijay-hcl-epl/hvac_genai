/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and unit setup.
 *
 * Traces: SWE-REQ-020
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdbool.h>

/**
 * @brief Perform full system initialisation.
 *        Configures HAL, clocks, and invokes Init for every software unit.
 *        Ensures motor is OFF and reads initial feedback to set LEDs.
 *        [SWE-REQ-020, SWE-REQ-021]
 * @return true if all units initialised successfully, false on error.
 */
bool SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
