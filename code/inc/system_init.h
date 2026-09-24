/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and module init.
 *
 * Traces: SWE-REQ-020
 *
 * Initialises clocks, HAL, all software unit modules, reads initial
 * feedback, sets power LED, and ensures the motor is off on startup.
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdint.h>

/**
 * @brief Perform full system initialisation.
 *        Calls HAL_Init, SystemClock_Config, and all module Init functions.
 *        Reads initial feedback position, sets power LED, ensures motor off.
 *        [SWE-REQ-020, SWE-REQ-021]
 * @return 0 on success, non-zero on error.
 */
uint8_t SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
