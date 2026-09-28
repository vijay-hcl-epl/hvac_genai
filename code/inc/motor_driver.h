/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO/PWM control for L298N H-bridge DC motor.
 *
 * Software Unit : Motor Driver
 * Traceability  : SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *                 SWE-REQ-036, SWE-REQ-038
 *
 * CONFIGURATION GAP: GPIO pins for IN1/IN2/ENA and the timer/channel used
 * for PWM are assumed defaults.  They MUST be validated against the actual
 * L298N wiring and STM32F407G-DISC1 board connections.
 */
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/* Motor direction enumeration */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,
    MOTOR_DIR_FORWARD = 1U,
    MOTOR_DIR_REVERSE = 2U
} MotorDir_t;

/* Motor status */
typedef enum
{
    MOTOR_STATUS_OK    = 0U,
    MOTOR_STATUS_FAULT = 1U
} MotorStatus_t;

/* ── PWM duty configuration ────────────────────────────────────────────
 * CONFIGURATION GAP: Default duty cycle for movement.  Must be tuned
 * per mechanical load and 12 V supply characteristics.
 * ──────────────────────────────────────────────────────────────────── */
#define MOTOR_DEFAULT_DUTY_PERCENT  ((uint8_t)70U)

/**
 * @brief Initialise motor driver (outputs OFF / safe state).
 * Trace: SWE-REQ-020 (via System Init), SWE-REQ-008
 */
void MotorDrv_Init(void);

/**
 * @brief Drive motor in the given direction with enable.
 * Trace: SWE-REQ-007, SWE-REQ-016
 *
 * @param dir     Direction (FORWARD / REVERSE).
 * @param enable  1 = enable PWM output, 0 = coast/disable.
 */
void MotorDrv_Drive(MotorDir_t dir, uint8_t enable);

/**
 * @brief Immediately stop motor – all outputs off (safe state).
 * Trace: SWE-REQ-008, SWE-REQ-025
 */
void MotorDrv_Stop(void);

/**
 * @brief Get current motor status.
 * Trace: SWE-REQ-039 (testability)
 *
 * @return MotorStatus_t (OK or FAULT).
 */
MotorStatus_t MotorDrv_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
