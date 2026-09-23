/**
 * @file motor_driver.h
 * @brief Motor Driver – DC motor GPIO/PWM actuation via L298N H-Bridge.
 *
 * Software Unit: Motor Driver
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (GPIO + TIM PWM)
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/** Motor direction enumeration */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD = 1U,
    MOTOR_DIR_REVERSE = 2U
} MotorDirection_t;

/** Motor status enumeration */
typedef enum
{
    MOTOR_STATUS_IDLE    = 0U,
    MOTOR_STATUS_RUNNING = 1U,
    MOTOR_STATUS_FAULT   = 2U
} MotorStatus_t;

/** Default PWM duty cycle (percent) for motor actuation.
 *  Configurable responsiveness parameter [SWE-REQ-035]. */
#define MOTOR_DEFAULT_PWM_DUTY  ((uint8_t)70U)

/**
 * @brief Initialise the Motor Driver unit.
 *        GPIO + PWM timer configured; motor outputs OFF (safe state).
 *        [SWE-REQ-020]
 */
void MotorDriver_Init(void);

/**
 * @brief Drive the motor in the specified direction.
 * @param dir     Motor direction (FORWARD / REVERSE).
 * @param enable  true = run, false = coast-stop.
 *        [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDirection_t dir, bool enable);

/**
 * @brief Immediately stop the motor (all outputs off / safe state).
 *        [SWE-REQ-008, SWE-REQ-025]
 */
void MotorDriver_Stop(void);

/**
 * @brief Get current motor status.
 * @return MotorStatus_t
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
