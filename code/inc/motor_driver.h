/**
 * @file motor_driver.h
 * @brief Motor Driver – GPIO direction + PWM enable for L298N H-Bridge.
 *
 * Software Unit: Motor Driver
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL / L298N
 *
 * ASSUMPTIONS (not verified on hardware):
 *   - IN1 (direction A) : PB0  GPIO output
 *   - IN2 (direction B) : PB1  GPIO output
 *   - ENA (PWM enable)  : PA0  TIM2_CH1 PWM output
 *   - PWM frequency and duty are design assumptions; calibrate for motor.
 *   Pin and timer assignments are placeholders – update per actual wiring.
 */
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

/** Motor direction commands. */
typedef enum
{
    MOTOR_DIR_STOP    = 0U,   /**< Both direction pins LOW – coast stop.  */
    MOTOR_DIR_FORWARD = 1U,   /**< IN1=HIGH, IN2=LOW  – assumed CW.      */
    MOTOR_DIR_REVERSE = 2U    /**< IN1=LOW,  IN2=HIGH – assumed CCW.      */
} motor_dir_t;

/** Motor status. */
typedef enum
{
    MOTOR_STATUS_STOPPED = 0U,
    MOTOR_STATUS_RUNNING = 1U,
    MOTOR_STATUS_FAULT   = 2U
} motor_status_t;

/**
 * @brief Initialise motor outputs to safe state (stopped).
 * Traces: SWE-REQ-020, SWE-REQ-008
 */
void motor_driver_init(void);

/**
 * @brief Drive the motor in the specified direction.
 *
 * Sets GPIO direction pins and starts PWM at a fixed duty cycle.
 *
 * Traces: SWE-REQ-007, SWE-REQ-016
 *
 * @param dir     Desired direction.
 * @param enable  true = motor ON at configured duty; false = motor OFF.
 */
void motor_driver_drive(motor_dir_t dir, uint8_t enable);

/**
 * @brief Immediately stop motor (safe state).
 * Traces: SWE-REQ-008, SWE-REQ-025, SWE-REQ-032
 */
void motor_driver_stop(void);

/**
 * @brief Return the current motor status.
 */
motor_status_t motor_driver_get_status(void);

#endif /* MOTOR_DRIVER_H */
