/**
 * @file led_status_handler.h
 * @brief LED Status Handler – Power/position LEDs, one-hot indication, event-driven.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 * Platform: STM32F407G-DISC1 / STM32 HAL / GPIO
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Number of position LEDs (one per flap position) */
#define LED_NUM_POSITIONS       (5U)

/**
 * @brief Initialise LED GPIO pins and set default states (power LED ON, others OFF).
 */
void led_status_init(void);

/**
 * @brief Set the power / running LED state.
 * @param on  1 = ON, 0 = OFF.
 */
void led_status_set_power(uint8_t on);

/**
 * @brief Update position LEDs to indicate the given position (one-hot).
 *        Only one green position LED is ON at a time.
 * @param position  Logical position (1–5). 0 or invalid turns all position LEDs OFF.
 */
void led_status_set_position(uint8_t position);

/**
 * @brief Indicate an error condition on LEDs (implementation-defined pattern).
 */
void led_status_indicate_error(void);

#endif /* LED_STATUS_HANDLER_H */
