/**
 * @file motor_driver.h
 * @brief Motor Driver Software Unit – Header
 *
 * Drives the DC motor through GPIO (direction) and PWM (enable/speed)
 * via the L298N motor driver module.  Enforces safe-stop on error.
 *
 * Traceability:
 *   SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *   SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal, L298N H-Bridge
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Motor direction enumeration.
 *        [SWE-REQ-007]
 */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,  /**< Motor stopped / coast        */
    MOTOR_DIR_FORWARD = 1U,  /**< Rotate forward (flap open)   */
    MOTOR_DIR_REVERSE = 2U   /**< Rotate reverse (flap close)  */
} MotorDirection_t;

/**
 * @brief Motor status enumeration.
 *        [SWE-REQ-008, SWE-REQ-025]
 */
typedef enum
{
    MOTOR_STATUS_STOPPED  = 0U,
    MOTOR_STATUS_RUNNING  = 1U,
    MOTOR_STATUS_FAULT    = 2U
} MotorStatus_t;

/**
 * @brief Default PWM duty cycle (%) for motor enable.
 *        Configurable responsiveness parameter [SWE-REQ-035].
 */
#define MOTOR_DEFAULT_DUTY_PERCENT  (75U)

/**
 * @brief Initialise the Motor Driver unit.
 *        Sets all outputs to safe (motor OFF).
 *        [SWE-REQ-020, SWE-REQ-008]
 */
void MotorDriver_Init(void);

/**
 * @brief Drive the motor in the specified direction.
 * @param dir    Desired direction (FORWARD / REVERSE / STOP).
 * @param enable true to enable motor, false to disable.
 *        [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDirection_t dir, bool enable);

/**
 * @brief Immediately stop the motor (all outputs OFF, safe state).
 *        [SWE-REQ-008, SWE-REQ-025, SWE-REQ-032]
 */
void MotorDriver_Stop(void);

/**
 * @brief Retrieve current motor status.
 * @return MotorStatus_t
 *        [SWE-REQ-040]
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
