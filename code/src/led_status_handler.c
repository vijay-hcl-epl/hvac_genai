/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation – power LED, one-hot position LEDs, error.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * Pin mapping (assumed from STM32F407 Discovery board and env-setup):
 *   Power LED      : PD12 (Green on-board LED)
 *   Position LED 0 : PE0
 *   Position LED 1 : PE1
 *   Position LED 2 : PE2
 *   Position LED 3 : PE3
 *   Position LED 4 : PE4
 *   Error LED      : PD14 (Red on-board LED)
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- Pin definitions (SWE-REQ-018, env-setup: GPIO LED control) ---- */

/** Power LED */
#define LED_POWER_PORT      GPIOD
#define LED_POWER_PIN       GPIO_PIN_12

/** Error LED */
#define LED_ERROR_PORT      GPIOD
#define LED_ERROR_PIN       GPIO_PIN_14

/** Position LED ports – all on GPIOE for expansion LEDs */
#define LED_POS_PORT        GPIOE

/** Position LED pin table (SWE-REQ-038) */
static const uint16_t g_pos_led_pin[LED_NUM_POSITIONS] =
{
    GPIO_PIN_0,   /* Position 0 */
    GPIO_PIN_1,   /* Position 1 */
    GPIO_PIN_2,   /* Position 2 */
    GPIO_PIN_3,   /* Position 3 */
    GPIO_PIN_4    /* Position 4 */
};

/* ---- Internal static state (SWE-REQ-009, SWE-REQ-036) ---- */

static uint8_t g_current_pos_led;  /**< Currently lit position LED index, 0xFF = none */

/* ================================================================== */

/**
 * @brief Turn off all position LEDs.
 */
static void LedStatus_AllPositionOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(LED_POS_PORT, g_pos_led_pin[i], GPIO_PIN_RESET);
    }
    g_current_pos_led = 0xFFU;
}

/* ================================================================== */

void LedStatus_Init(void)
{
    /* All position LEDs off, error LED off */
    LedStatus_AllPositionOff();
    HAL_GPIO_WritePin(LED_ERROR_PORT, LED_ERROR_PIN, GPIO_PIN_RESET);

    /* Power LED ON (SWE-REQ-012) */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);

    g_current_pos_led = 0xFFU;
}

/* ------------------------------------------------------------------ */

void LedStatus_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

/* ------------------------------------------------------------------ */

void LedStatus_SetPositionLed(uint8_t position)
{
    /* Only change on valid event and if position actually changed (SWE-REQ-014) */
    if (position >= LED_NUM_POSITIONS)
    {
        return;
    }

    if (position == g_current_pos_led)
    {
        return;  /* No change needed */
    }

    /* Clear error LED on valid position event */
    HAL_GPIO_WritePin(LED_ERROR_PORT, LED_ERROR_PIN, GPIO_PIN_RESET);

    /* One-hot: turn off all, then turn on the one (SWE-REQ-013) */
    LedStatus_AllPositionOff();
    HAL_GPIO_WritePin(LED_POS_PORT, g_pos_led_pin[position], GPIO_PIN_SET);
    g_current_pos_led = position;
}

/* ------------------------------------------------------------------ */

void LedStatus_IndicateError(void)
{
    /* Turn on error LED, do NOT change position LEDs (SWE-REQ-014) */
    HAL_GPIO_WritePin(LED_ERROR_PORT, LED_ERROR_PIN, GPIO_PIN_SET);
}
