/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED and position indication LEDs.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Controls the power/init LED and per-position green LEDs.
 * Enforces one-hot position indication (at most one green LED ON).
 * State changes only on valid command or position-change events.
 * No dynamic allocation.
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Number of position LEDs */
#define LED_NUM_POSITIONS  (5U)

/**
 * @brief Initialise LED GPIO outputs, turn all position LEDs off,
 *        power LED off (will be set by system_init).
 *        [SWE-REQ-020]
 */
void LedStatus_Init(void);

/**
 * @brief Turn on the power / initialisation LED.
 *        [SWE-REQ-012]
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief Update position LED indication.
 *        Turns off all green LEDs, then turns on the one corresponding
 *        to the given position (1-hot).
 * @param position  Logical flap position (1..5).  0 = all off.
 *        [SWE-REQ-013, SWE-REQ-014]
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief Indicate error state on LEDs (e.g. blink pattern or all off).
 *        [SWE-REQ-032]
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
