/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and unit init.
 *
 * Traces: SWE-REQ-020
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdint.h>

/**
 * @brief Perform full system initialisation.
 *
 * Initialises STM32 HAL, clocks, GPIO, UART, ADC, PWM timer,
 * then initialises all software units and sets safe initial states.
 *
 * Traces: SWE-REQ-020
 */
void SystemInit_Run(void);

#endif /* SYSTEM_INIT_H */
