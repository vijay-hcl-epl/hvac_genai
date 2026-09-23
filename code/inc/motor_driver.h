/**
 * @file    motor_driver.h
 * @brief   Motor Driver software unit – header.
 *
 * Drives the DC motor via GPIO direction pins and PWM enable,
 * interfacing with the L298N H-Bridge driver module.
 *
 * Traceability:
 *   SWE-REQ-007  – Set GPIO and PWM outputs for motor enable/direction.
 *   SWE-REQ-008  – Immediately stop motor on invalid feedback or target reached.
 *   SWE-REQ-016  – Control DC motor using GPIO/PWM exclusively.
 *   SWE-REQ-025  – Cease all motor outputs on error/fault.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *   SWE-REQ-038  – All limits declared statically.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL, L298N H-Bridge.
 */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/* ---- Public Types --------------------------------------------------- */

/** @brief Motor rotation direction. */
typedef enum
{
    MOTOR_DIR_CW  = 0U,   /**< Clockwise (increase position)     */
    MOTOR_DIR_CCW = 1U    /**< Counter-clockwise (decrease pos.)  */
} MotorDirection_t;

/** @brief Motor status for external query (SWE-REQ-040). */
typedef enum
{
    MOTOR_STATUS_STOPPED = 0U,
    MOTOR_STATUS_RUNNING,
    MOTOR_STATUS_FAULT
} MotorStatus_t;

/* ---- Public Constants ----------------------------------------------- */

/** @brief Default PWM duty-cycle percentage for motor drive.
 *  Configurable responsiveness parameter (SWE-REQ-035). */
#define MOTOR_DEFAULT_DUTY_PERCENT  (75U)

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  Initialise motor driver – outputs OFF, safe state.
 *         [SWE-REQ-020, SWE-REQ-008]
 */
void MotorDriver_Init(void);

/**
 * @brief  Drive motor in given direction with enable.
 * @param  dir     MOTOR_DIR_CW or MOTOR_DIR_CCW.
 * @param  enable  true = run, false = coast.
 *         [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDirection_t dir, bool enable);

/**
 * @brief  Immediately stop all motor outputs (safe state).
 *         [SWE-REQ-008, SWE-REQ-025, SWE-REQ-032]
 */
void MotorDriver_Stop(void);

/**
 * @brief  Return current motor status.
 *         [SWE-REQ-040]
 */
MotorStatus_t MotorDriver_GetStatus(void);

#endif /* MOTOR_DRIVER_H */
