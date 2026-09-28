/**
 * @file system_init.h
 * @brief System Startup / Initialisation – one-time peripheral and unit init.
 *
 * Software Unit : System Startup/Initialization
 * Traceability  : SWE-REQ-020
 */
#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

/**
 * @brief Perform full system initialisation:
 *        1. HAL init (clocks, SysTick).
 *        2. Peripheral init (UART, ADC, GPIO, PWM/Timer).
 *        3. Software-unit init (all units).
 *        4. Ensure motor is OFF (safe state).
 *        5. Read initial feedback and set LEDs.
 * Trace: SWE-REQ-020, SWE-REQ-021
 */
void System_Init(void);

#endif /* SYSTEM_INIT_H */
