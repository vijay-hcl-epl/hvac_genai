/**
 * @file    led_status_handler.h
 * @brief   LED Status Handler software unit – header.
 *
 * Controls power/run LED and position-indicating green LEDs.
 * Enforces one-hot green LED rule.  Changes only on valid event.
 *
 * Traceability:
 *   SWE-REQ-012  – Activate power LED on startup / running.
 *   SWE-REQ-013  – Indicate position with corresponding green LED (one-hot).
 *   SWE-REQ-014  – Alter LED state only on valid command / position change.
 *   SWE-REQ-018  – Use discrete logical output controls for LEDs.
 *   SWE-REQ-021  – Indicate initial state on LEDs after startup.
 *   SWE-REQ-039  – Log/indicate position via status LEDs.
 *   SWE-REQ-036  – No dynamic memory allocation.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 */

#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

/* ---- Public Constants ----------------------------------------------- */

/** @brief Number of position LEDs (one per flap position). */
#define LED_NUM_POSITIONS  (5U)

/* ---- Public API ----------------------------------------------------- */

/**
 * @brief  Initialise LED handler – all LEDs off.
 *         [SWE-REQ-020]
 */
void LedStatus_Init(void);

/**
 * @brief  Turn ON the power/run LED.
 *         [SWE-REQ-012]
 */
void LedStatus_SetPowerLed(void);

/**
 * @brief  Update position LEDs – one-hot: only LED for @p position is ON.
 * @param  position  Logical position 0..4.
 *         [SWE-REQ-013, SWE-REQ-014]
 */
void LedStatus_SetPosition(uint8_t position);

/**
 * @brief  Indicate error state on LEDs (all position LEDs OFF, power LED stays).
 *         [SWE-REQ-032]
 */
void LedStatus_IndicateError(void);

#endif /* LED_STATUS_HANDLER_H */
