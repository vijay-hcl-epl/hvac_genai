/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, GPIO-driven LEDs, bare-metal
 *
 * LED mapping (assumed Discovery board + external LEDs):
 *   Power LED       : PD12 (Green on-board)
 *   Position 0 LED  : PE0
 *   Position 1 LED  : PE1
 *   Position 2 LED  : PE2
 *   Position 3 LED  : PE3
 *   Position 4 LED  : PE4
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Pin configuration tables (SWE-REQ-030, SWE-REQ-038) ---------- */

/** GPIO port for position LEDs */
static GPIO_TypeDef * const g_pos_led_port[LED_NUM_POSITIONS] =
{
    GPIOE, GPIOE, GPIOE, GPIOE, GPIOE
};

/** GPIO pin for each position LED */
static const uint16_t g_pos_led_pin[LED_NUM_POSITIONS] =
{
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4
};

/** Power LED port and pin */
#define POWER_LED_PORT  GPIOD
#define POWER_LED_PIN   GPIO_PIN_12

/* ---------- Static data ---------- */

/** Currently active position LED index (0xFF = none) */
static uint8_t g_active_led = 0xFFU;

/* ---------- Private helpers ---------- */

/**
 * @brief Turn all position LEDs off.
 */
static void AllPositionLedsOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(g_pos_led_port[i], g_pos_led_pin[i], GPIO_PIN_RESET);
    }
    g_active_led = 0xFFU;
}

/* ---------- Public API ---------- */

void LedStatus_Init(void)
{
    AllPositionLedsOff();
    /* Power LED off initially – will be set explicitly */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_RESET);
}

void LedStatus_SetPowerLed(void)
{
    /* SWE-REQ-012: power LED ON */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

void LedStatus_SetPosition(uint8_t position)
{
    if (position >= LED_NUM_POSITIONS)
    {
        return; /* Out of range – safety guard */
    }

    /* SWE-REQ-014: only alter on change */
    if (position == g_active_led)
    {
        return;
    }

    /* SWE-REQ-013: one-hot – turn off all, then set the target */
    AllPositionLedsOff();
    HAL_GPIO_WritePin(g_pos_led_port[position], g_pos_led_pin[position], GPIO_PIN_SET);
    g_active_led = position;
}

void LedStatus_IndicateError(void)
{
    /* SWE-REQ-032: safe indication – turn off all position LEDs */
    AllPositionLedsOff();
}
