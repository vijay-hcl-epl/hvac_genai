/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED, position LEDs (one-hot), error indication.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Maximum number of position LEDs (matches CMD_NUM_POSITIONS) */
#define LED_NUM_POSITIONS  (5U)

/**
 * @brief Initialise all LED GPIO outputs; turn all position LEDs off.
 *
 * Traces: SWE-REQ-020
 */
void LedStatus_Init(void);

/**
 * @brief Activate the power / running indication LED.
 *
 * Traces: SWE-REQ-012
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Update position LEDs – one-hot: only the LED for @p position is ON.
 *
 * @param position  Logical flap position (0..4).
 *
 * Traces: SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-039
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief Indicate an error / fault state on LEDs.
 *
 * Turns off all position LEDs (no misleading indication).
 *
 * Traces: SWE-REQ-032
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
