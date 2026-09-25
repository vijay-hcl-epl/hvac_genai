/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO/PWM control for L298N DC motor via STM32 HAL.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 * Platform: STM32F407G-DISC1 / STM32 HAL / L298N
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/** Motor direction enumeration */
typedef enum
{
    MOTOR_DIR_STOP = 0U,
    MOTOR_DIR_FORWARD,
    MOTOR_DIR_REVERSE
} motor_direction_t;

/** Motor status */
typedef enum
{
    MOTOR_STATUS_STOPPED = 0U,
    MOTOR_STATUS_RUNNING,
    MOTOR_STATUS_ERROR
} motor_status_t;

/** Default PWM duty cycle (percentage, 0–100) */
#define MOTOR_DEFAULT_DUTY      (70U)

/**
 * @brief Initialise motor driver GPIO/PWM peripherals and ensure motor is stopped.
 */
void motor_driver_init(void);

/**
 * @brief Drive the motor in the specified direction.
 * @param dir     MOTOR_DIR_FORWARD or MOTOR_DIR_REVERSE.
 * @param enable  1 = enable motor, 0 = disable (coast).
 */
void motor_driver_drive(motor_direction_t dir, uint8_t enable);

/**
 * @brief Immediately stop the motor (all outputs off – safe state).
 */
void motor_driver_stop(void);

/**
 * @brief Get current motor status.
 * @return motor_status_t value.
 */
motor_status_t motor_driver_get_status(void);

#endif /* MOTOR_DRIVER_H */
