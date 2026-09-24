/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO / PWM control for DC motor via L298N.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, L298N H-Bridge, bare-metal
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/** Motor direction identifiers */
#define MOTOR_DIR_FORWARD  (0U)
#define MOTOR_DIR_REVERSE  (1U)

/** Motor enable / disable */
#define MOTOR_ENABLE       (1U)
#define MOTOR_DISABLE      (0U)

/** Default PWM duty cycle (percentage 0..100) for motor speed – configurable constant (SWE-REQ-035) */
#define MOTOR_DEFAULT_DUTY (70U)

/** Motor status codes */
#define MOTOR_STATUS_OK    (0U)
#define MOTOR_STATUS_FAULT (1U)

/**
 * @brief Initialise motor driver GPIO and PWM peripherals.
 *
 * Ensures motor is OFF on startup (SWE-REQ-020).
 *
 * Traces: SWE-REQ-020
 */
void MotorDriver_Init(void);

/**
 * @brief Drive motor in the specified direction.
 *
 * @param direction  MOTOR_DIR_FORWARD or MOTOR_DIR_REVERSE.
 * @param enable     MOTOR_ENABLE or MOTOR_DISABLE.
 *
 * Traces: SWE-REQ-007, SWE-REQ-016
 */
void MotorDriver_Drive(uint8_t direction, uint8_t enable);

/**
 * @brief Immediately stop the motor (all outputs off / safe state).
 *
 * Traces: SWE-REQ-008, SWE-REQ-025
 */
void MotorDriver_Stop(void);

/**
 * @brief Get the current motor status.
 *
 * @return MOTOR_STATUS_OK or MOTOR_STATUS_FAULT.
 */
uint8_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
