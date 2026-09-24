/**
 * @file motor_driver.h
 * @brief Motor Driver – DC motor GPIO/PWM control via L298N.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Provides abstracted motor control: direction, enable (PWM), and
 * emergency stop.  Uses STM32 HAL GPIO and TIM PWM peripherals.
 * No dynamic allocation.
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/** Motor direction */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD = 1U,
    MOTOR_DIR_REVERSE = 2U
} MotorDir_t;

/** Motor status */
typedef enum
{
    MOTOR_STATUS_STOPPED = 0U,
    MOTOR_STATUS_RUNNING = 1U,
    MOTOR_STATUS_FAULT   = 2U
} MotorStatus_t;

/**
 * @brief Initialise motor GPIO/PWM outputs; motor OFF, direction cleared.
 *        [SWE-REQ-020]
 */
void MotorDriver_Init(void);

/**
 * @brief Drive the motor in the specified direction with enable.
 * @param dir     MOTOR_DIR_FORWARD or MOTOR_DIR_REVERSE
 * @param enable  1 = enable (PWM on), 0 = coast/disable
 *        [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDir_t dir, uint8_t enable);

/**
 * @brief Immediately stop the motor (all outputs off / safe state).
 *        [SWE-REQ-008, SWE-REQ-025]
 */
void MotorDriver_Stop(void);

/**
 * @brief Return current motor status.
 * @return MotorStatus_t
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
