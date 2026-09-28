/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation.
 *
 * Software Unit : LED Status Handler
 * Traceability  : SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *                 SWE-REQ-021, SWE-REQ-039
 *
 * Platform      : STM32F407G-DISC1, STM32 HAL
 *
 * CONFIGURATION GAP: GPIO port/pin assignments for each position LED and
 * the power LED are ASSUMED placeholders.  The STM32F407G-DISC1 board has
 * four on-board user LEDs (PD12-green, PD13-orange, PD14-red, PD15-blue).
 * For five position LEDs an external LED circuit is assumed.  Pin mapping
 * below MUST be validated/updated during hardware integration.
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ── Pin configuration table (ASSUMED – see gap note above) ──────────
 * Power LED          : PD12 (on-board green LED re-used as power indicator)
 * Position LED 0..4  : PE0 .. PE4  (external LEDs, directly driven GPIO)
 *
 * WARNING: These assignments are placeholders.  Integration must confirm
 * the actual schematic and update if different.
 * ──────────────────────────────────────────────────────────────────── */

#define POWER_LED_PORT      GPIOD
#define POWER_LED_PIN       GPIO_PIN_12

#define POS_LED_PORT        GPIOE

static const uint16_t s_pos_led_pins[5U] =
{
    GPIO_PIN_0,   /* Position 0 */
    GPIO_PIN_1,   /* Position 1 */
    GPIO_PIN_2,   /* Position 2 */
    GPIO_PIN_3,   /* Position 3 */
    GPIO_PIN_4    /* Position 4 */
};

#define POS_LED_COUNT       ((uint8_t)5U)

/* ── Static state (SWE-REQ-036) ──────────────────────────────────────── */
static uint8_t s_current_led_pos = 0xFFU;  /* No position indicated yet */

/* ── Private helpers ─────────────────────────────────────────────────── */

/** Turn OFF all position LEDs. */
static void AllPositionLedsOff(void)
{
    uint8_t i;
    for (i = 0U; i < POS_LED_COUNT; i++)
    {
        HAL_GPIO_WritePin(POS_LED_PORT, s_pos_led_pins[i], GPIO_PIN_RESET);
    }
}

/* ── Public API ──────────────────────────────────────────────────────── */

void LedStatus_Init(void)
{
    AllPositionLedsOff();
    s_current_led_pos = 0xFFU;

    /* SWE-REQ-012: Power LED ON at startup. */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

void LedStatus_SetPosition(uint8_t position)
{
    /* SWE-REQ-014: only alter on valid event; SWE-REQ-013: one-hot. */
    if (position >= POS_LED_COUNT)
    {
        return;  /* Out of range – no change. */
    }

    if (position == s_current_led_pos)
    {
        return;  /* No change needed. */
    }

    /* One-hot: turn all OFF, then the indicated one ON. */
    AllPositionLedsOff();
    HAL_GPIO_WritePin(POS_LED_PORT, s_pos_led_pins[position], GPIO_PIN_SET);
    s_current_led_pos = position;
}

void LedStatus_SetPowerLed(void)
{
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

void LedStatus_IndicateError(void)
{
    /* SWE-REQ-032: safe idle – turn off position LEDs, power LED stays. */
    AllPositionLedsOff();
    s_current_led_pos = 0xFFU;
    /* Power LED remains ON (no change). */
}
