/**
 * @file motor_driver.h
 * @brief Motor Driver – DC motor GPIO/PWM control via L298N H-Bridge.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/**
 * @brief Motor direction enumeration.
 *
 * Traces: SWE-REQ-007
 */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD = 1U,
    MOTOR_DIR_REVERSE = 2U
} MotorDirection_t;

/**
 * @brief Motor status.
 *
 * Traces: SWE-REQ-008
 */
typedef enum
{
    MOTOR_STATUS_STOPPED = 0U,
    MOTOR_STATUS_RUNNING = 1U,
    MOTOR_STATUS_FAULT   = 2U
} MotorStatus_t;

/**
 * @brief Initialise motor driver outputs to safe state (motor OFF).
 *
 * Traces: SWE-REQ-020, SWE-REQ-008
 */
void MotorDriver_Init(void);

/**
 * @brief Drive the motor in a specified direction.
 *
 * Sets GPIO direction pins and PWM enable via STM32 HAL.
 *
 * @param[in] direction  Desired motor direction.
 * @param[in] enable     1 = enable motor, 0 = disable.
 *
 * Traces: SWE-REQ-007, SWE-REQ-016
 */
void MotorDriver_Drive(MotorDirection_t direction, uint8_t enable);

/**
 * @brief Immediately stop the motor (safe state).
 *
 * Traces: SWE-REQ-008, SWE-REQ-025
 */
void MotorDriver_Stop(void);

/**
 * @brief Get current motor status.
 *
 * @return MotorStatus_t  Current status.
 *
 * Traces: SWE-REQ-008
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
