/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power/position LED control, one-hot indication.
 *
 * Software Unit : LED Status Handler
 * Traceability  : SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *                 SWE-REQ-021, SWE-REQ-039
 *
 * CONFIGURATION GAP: The GPIO ports/pins for each position LED and the
 * power LED are assumed placeholders.  Actual assignments must match
 * the STM32F407G-DISC1 board wiring confirmed during integration.
 */
#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/**
 * @brief Initialise LED handler – all position LEDs OFF, power LED ON.
 * Trace: SWE-REQ-012, SWE-REQ-020 (via System Init)
 */
void LedStatus_Init(void);

/**
 * @brief Set position LED (one-hot: only the indicated position LED ON,
 *        all others OFF).  Only call on valid position change event
 *        (SWE-REQ-014).
 * Trace: SWE-REQ-013, SWE-REQ-014, SWE-REQ-018
 *
 * @param position  Logical flap position (0..4).
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief Turn on the power/run indicator LED.
 * Trace: SWE-REQ-012
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Indicate an error condition via LEDs.
 *        Implementation: all position LEDs OFF (safe), power LED stays ON.
 * Trace: SWE-REQ-032, SWE-REQ-039
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
