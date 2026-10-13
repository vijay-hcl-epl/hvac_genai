/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED, one-hot position LEDs, error indication.
 *
 * Software Unit: LED Status Handler
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL GPIO
 *
 * ASSUMPTIONS (not verified on hardware):
 *   - Power LED            : PD12 (Green on Discovery board)
 *   - Position LED 1..4    : PD13, PD14, PD15, PE0  (design assumption – adjust to wiring)
 *   - Position LED 5 / Err : PE1  (shared or separate – adjust to wiring)
 *   Pin assignments are placeholders; update to match actual board wiring.
 */
#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Maximum number of position LEDs (must match FB_NUM_POSITIONS). */
#define LED_NUM_POSITIONS  5U

/**
 * @brief Initialise LED outputs (all OFF).
 * Traces: SWE-REQ-020
 */
void led_status_init(void);

/**
 * @brief Turn on the power / running indicator LED.
 * Traces: SWE-REQ-012
 */
void led_status_set_power(void);

/**
 * @brief Set position LED – one-hot: only the LED for `position` is ON.
 *
 * Traces: SWE-REQ-013, SWE-REQ-014, SWE-REQ-039
 *
 * @param position  Flap position 1..LED_NUM_POSITIONS.  0 = all position LEDs off.
 */
void led_status_set_position(uint8_t position);

/**
 * @brief Indicate an error state on the LEDs.
 *
 * Traces: SWE-REQ-014, SWE-REQ-032
 */
void led_status_indicate_error(void);

#endif /* LED_STATUS_HANDLER_H */
