/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED, position indication (one-hot), error indication.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Maximum number of position LEDs (green) */
#define LED_NUM_POSITIONS  (5U)

/**
 * @brief Initialise LED outputs (all OFF except power LED ON).
 *
 * Traces: SWE-REQ-012, SWE-REQ-020
 */
void LedStatus_Init(void);

/**
 * @brief Activate the power / initialisation LED.
 *
 * Traces: SWE-REQ-012
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Update position LED to reflect current flap position (one-hot).
 *
 * Only one green LED is ON at a time (SWE-REQ-013).
 * State changed only on valid event (SWE-REQ-014).
 *
 * @param[in] position  Flap position (0..LED_NUM_POSITIONS-1).
 *
 * Traces: SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-039
 */
void LedStatus_SetPositionLed(uint8_t position);

/**
 * @brief Indicate error state on LEDs.
 *
 * Traces: SWE-REQ-014, SWE-REQ-039
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
