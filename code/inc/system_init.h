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
 * @brief Perform full system initialisation.
 *
 * Initialises HAL, clocks, GPIO, UART, ADC, PWM timer, then initialises
 * every software unit and sets safe output states.
 * Reads initial feedback and indicates state on LEDs.
 *
 * Traces: SWE-REQ-020, SWE-REQ-021
 */
void system_init(void);

#endif /* SYSTEM_INIT_H */
