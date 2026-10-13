/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and module init.
 *
 * Software Unit : System Startup/Initialization
 * Traces        : SWE-REQ-020
 * Platform      : STM32F407G-DISC1, STM32 HAL
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdint.h>

/**
 * @brief Perform full system initialisation.
 *        Initialises HAL, clocks, GPIO, UART, ADC, PWM timer,
 *        then initialises every application software unit and
 *        sets the system to a safe idle state.
 * Traces: SWE-REQ-020
 */
void SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
