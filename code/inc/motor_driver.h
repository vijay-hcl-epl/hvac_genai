/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO/PWM control for L298N DC motor driver.
 *
 * Software Unit : Motor Driver
 * Traces        : SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *                 SWE-REQ-036, SWE-REQ-038
 * Platform      : STM32F407G-DISC1, L298N H-Bridge, Timer-based PWM
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/** Motor direction */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD,
    MOTOR_DIR_REVERSE
} MotorDirection_t;

/** Motor status */
typedef enum
{
    MOTOR_STATUS_IDLE  = 0U,
    MOTOR_STATUS_RUNNING,
    MOTOR_STATUS_FAULT
} MotorStatus_t;

/** Motor driver static data */
typedef struct
{
    MotorDirection_t direction;   /**< Current direction setting */
    uint8_t          enable;      /**< 1 = enabled, 0 = disabled */
    uint16_t         pwmDuty;     /**< PWM duty cycle (0..max period) */
    MotorStatus_t    status;
} MotorDriverData_t;

/** Default PWM duty for active motor (configurable constant)
 *  Traces: SWE-REQ-035, SWE-REQ-038 */
#define MOTOR_DEFAULT_PWM_DUTY  ((uint16_t)500U)

/**
 * @brief Initialise motor driver outputs (motor OFF, safe state).
 * Traces: SWE-REQ-020
 */
void MotorDriver_Init(void);

/**
 * @brief Drive motor in the specified direction.
 * @param dir     MOTOR_DIR_FORWARD or MOTOR_DIR_REVERSE.
 * @param enable  1 = start, 0 = coast.
 * Traces: SWE-REQ-007, SWE-REQ-016
 */
void MotorDriver_Drive(MotorDirection_t dir, uint8_t enable);

/**
 * @brief Immediately stop motor (safe state).
 * Traces: SWE-REQ-008, SWE-REQ-025
 */
void MotorDriver_Stop(void);

/**
 * @brief Get current motor status.
 * Traces: SWE-REQ-040
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
