/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation – Power/position LED control.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 * Platform: STM32F407G-DISC1 / STM32 HAL / GPIO
 *
 * Pin mapping (assumed, configurable):
 *   Power LED   : PD12 (Green on Discovery board)
 *   Position 1  : PE0
 *   Position 2  : PE1
 *   Position 3  : PE2
 *   Position 4  : PE3
 *   Position 5  : PE4
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- Pin configuration (static constants) [SWE-REQ-030, SWE-REQ-038] ---- */

/** Power LED */
#define LED_POWER_PORT          GPIOD
#define LED_POWER_PIN           GPIO_PIN_12

/** Position LED GPIO port */
#define LED_POS_PORT            GPIOE

/** Position LED pins – array indexed 0..4 for positions 1..5 */
static const uint16_t s_pos_led_pins[LED_NUM_POSITIONS] =
{
    GPIO_PIN_0,   /* Position 1 */
    GPIO_PIN_1,   /* Position 2 */
    GPIO_PIN_2,   /* Position 3 */
    GPIO_PIN_3,   /* Position 4 */
    GPIO_PIN_4    /* Position 5 */
};

/* ---- Internal state (static) ---- */
static uint8_t s_current_pos_led;  /* Currently lit position (0 = none) */

/* ---- Private helpers ---- */

/** Turn all position LEDs OFF */
static void all_position_leds_off(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(LED_POS_PORT, s_pos_led_pins[i], GPIO_PIN_RESET);
    }
    s_current_pos_led = 0U;
}

/* ---- Public API ---- */

void led_status_init(void)
{
    /* Ensure all position LEDs are OFF */
    all_position_leds_off();

    /* Power LED ON at startup [SWE-REQ-012] */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

void led_status_set_power(uint8_t on)
{
    if (on != 0U)
    {
        HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_RESET);
    }
}

void led_status_set_position(uint8_t position)
{
    /* Only update on actual change [SWE-REQ-014] */
    if (position == s_current_pos_led)
    {
        return;
    }

    /* Turn all position LEDs OFF first (one-hot) [SWE-REQ-013] */
    all_position_leds_off();

    if ((position >= 1U) && (position <= LED_NUM_POSITIONS))
    {
        HAL_GPIO_WritePin(LED_POS_PORT, s_pos_led_pins[position - 1U], GPIO_PIN_SET);
        s_current_pos_led = position;
    }
    /* else: invalid position – all remain OFF */
}

void led_status_indicate_error(void)
{
    /* Error indication: turn all position LEDs OFF, keep power LED ON */
    all_position_leds_off();
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}
