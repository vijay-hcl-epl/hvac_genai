/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED, position indication, error display.
 *
 * Software Unit : LED Status Handler
 * Traces        : SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *                 SWE-REQ-021, SWE-REQ-039
 * Platform      : STM32F407G-DISC1, GPIO-based LEDs
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Number of position indicator LEDs (green) */
#define LED_NUM_POSITION_LEDS  ((uint8_t)5U)

/** LED identifiers (logical) */
#define LED_POWER_INDEX        ((uint8_t)0xFFU)  /**< Power / init LED */

/**
 * @brief Initialise LED outputs (all off, power LED on).
 * Traces: SWE-REQ-012, SWE-REQ-020
 */
void LedStatus_Init(void);

/**
 * @brief Set the position LED (one-hot: only the matching green LED ON).
 * @param position  Logical flap position 0..4.
 * Traces: SWE-REQ-013, SWE-REQ-014
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief Activate the power / initialisation LED.
 * Traces: SWE-REQ-012
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Indicate error state on LEDs (implementation-defined pattern).
 * Traces: SWE-REQ-032
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
