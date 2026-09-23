/**
 * @file led_status_handler.h
 * @brief LED Status Handler – power LED and one-hot position LED control.
 *
 * Software Unit: LED Status Handler
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (GPIO)
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/** Number of position LEDs (green) */
#define LED_NUM_POSITIONS   ((uint8_t)5U)

/**
 * @brief Initialise the LED Status Handler.
 *        All LEDs off initially.
 *        [SWE-REQ-020]
 */
void LedStatusHandler_Init(void);

/**
 * @brief Activate the power/initialisation LED.
 *        [SWE-REQ-012]
 */
void LedStatusHandler_SetPowerLed(void);

/**
 * @brief Set position indication LED (one-hot: only one green LED ON).
 * @param pos  Logical position (1..5). 0 = all position LEDs off.
 *        [SWE-REQ-013, SWE-REQ-014]
 */
void LedStatusHandler_SetLedState(uint8_t pos);

/**
 * @brief Indicate error state on LEDs.
 *        Turns off all position LEDs; power LED remains ON.
 *        [SWE-REQ-032]
 */
void LedStatusHandler_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
