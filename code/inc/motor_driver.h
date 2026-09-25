/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO direction, PWM enable, safe-stop for L298N via STM32 HAL.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *         SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, L298N H-Bridge, bare-metal
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/** Motor direction identifiers. */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD = 1U,
    MOTOR_DIR_REVERSE = 2U
} MotorDir_t;

/** Motor status. */
typedef enum
{
    MOTOR_STATUS_IDLE    = 0U,
    MOTOR_STATUS_RUNNING = 1U,
    MOTOR_STATUS_FAULT   = 2U
} MotorStatus_t;

/** Default PWM duty cycle (percent) for motor movement. */
#define MOTOR_DEFAULT_DUTY  ((uint8_t)75U)

/**
 * @brief Initialise motor driver GPIOs and PWM timer. Motor is OFF after init.
 *        [SWE-REQ-020]
 */
void MotorDriver_Init(void);

/**
 * @brief Drive the motor in the given direction with enable.
 * @param dir     MOTOR_DIR_FORWARD or MOTOR_DIR_REVERSE.
 * @param enable  true = run, false = coast stop.
 *        [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDir_t dir, bool enable);

/**
 * @brief Immediately stop all motor outputs (safe state).
 *        [SWE-REQ-008, SWE-REQ-025]
 */
void MotorDriver_Stop(void);

/**
 * @brief Return current motor status.
 * @return MotorStatus_t.
 *         [SWE-REQ-040]
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
