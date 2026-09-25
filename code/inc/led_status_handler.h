/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED, position LEDs (one-hot), error indication.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *         SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/**
 * @brief Initialise LED GPIOs and turn on the power/init LED.
 *        All position LEDs OFF.
 *        [SWE-REQ-012, SWE-REQ-020]
 */
void LedStatus_Init(void);

/**
 * @brief Set position indication LED (one-hot: exactly one green LED ON).
 * @param position  Logical position 1-5 (same encoding as command_parser).
 *        [SWE-REQ-013, SWE-REQ-014]
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief Activate the power / running LED.
 *        [SWE-REQ-012]
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Indicate an error state on LEDs (e.g. all position LEDs off, power blinks).
 *        [SWE-REQ-032]
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
