/**
 * @file led_status_handler.h
 * @brief LED Status Handler Software Unit – Header
 *
 * Controls the power/initialisation LED and per-position green LEDs.
 * Enforces one-hot position indication (at most one green LED ON).
 * State changes only on valid events.
 *
 * Traceability:
 *   SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *   SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/**
 * @brief Number of position LEDs (green).
 *        [SWE-REQ-013, SWE-REQ-038]
 */
#define LED_NUM_POSITIONS  (5U)

/**
 * @brief Initialise the LED Status Handler unit.
 *        All LEDs OFF except power LED.
 *        [SWE-REQ-012, SWE-REQ-020]
 */
void LedStatusHandler_Init(void);

/**
 * @brief Set the power/initialisation LED ON.
 *        [SWE-REQ-012]
 */
void LedStatusHandler_SetPowerLed(void);

/**
 * @brief Update the position LED to reflect a valid flap position.
 *        Enforces one-hot: turns OFF all position LEDs except the one
 *        corresponding to @p position.
 * @param position  Logical flap position (1..LED_NUM_POSITIONS).
 *                  0 or out-of-range turns all position LEDs OFF.
 *        [SWE-REQ-013, SWE-REQ-014]
 */
void LedStatusHandler_SetLedState(uint8_t position);

/**
 * @brief Indicate an error condition on LEDs.
 *        Implementation turns all position LEDs OFF (safe state).
 *        [SWE-REQ-032]
 */
void LedStatusHandler_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
