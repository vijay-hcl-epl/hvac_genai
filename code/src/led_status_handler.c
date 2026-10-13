/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation.
 *
 * Software Unit: LED Status Handler
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL GPIO
 * No dynamic allocation (SWE-REQ-036).  All state is static.
 *
 * ASSUMPTIONS / WIRING NOTE:
 *   Pin assignments below are PLACEHOLDERS based on the STM32F407 Discovery
 *   on-board LEDs (PD12-PD15) plus two extension GPIOs (PE0, PE1).
 *   Actual wiring MUST be confirmed before deployment.
 *
 *   Power LED        : PD12 (Green)
 *   Position LED 1   : PD13 (Orange)
 *   Position LED 2   : PD14 (Red)
 *   Position LED 3   : PD15 (Blue)
 *   Position LED 4   : PE0  (external)
 *   Position LED 5   : PE1  (external)
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- Pin mapping table (static, const) [SWE-REQ-030, SWE-REQ-038] ---- */

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} led_pin_t;

/** Power LED pin. */
static const led_pin_t s_power_led = { GPIOD, GPIO_PIN_12 };

/** Position LED pins (index 0 = Position 1, etc.). */
static const led_pin_t s_pos_leds[LED_NUM_POSITIONS] =
{
    { GPIOD, GPIO_PIN_13 },  /* Position 1 */
    { GPIOD, GPIO_PIN_14 },  /* Position 2 */
    { GPIOD, GPIO_PIN_15 },  /* Position 3 */
    { GPIOE, GPIO_PIN_0  },  /* Position 4 */
    { GPIOE, GPIO_PIN_1  }   /* Position 5 */
};

/* ---- Module static state ---- */

static uint8_t s_current_position_led = 0U;  /* 0 = none lit */

/* ---- Private helpers ---- */

/** Turn all position LEDs OFF. */
static void all_position_leds_off(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(s_pos_leds[i].port, s_pos_leds[i].pin, GPIO_PIN_RESET);
    }
    s_current_position_led = 0U;
}

/* ---- Public API ---- */

void led_status_init(void)
{
    /* All LEDs off at init */
    HAL_GPIO_WritePin(s_power_led.port, s_power_led.pin, GPIO_PIN_RESET);
    all_position_leds_off();
}

/* SWE-REQ-012 : power / running LED on */
void led_status_set_power(void)
{
    HAL_GPIO_WritePin(s_power_led.port, s_power_led.pin, GPIO_PIN_SET);
}

/*
 * SWE-REQ-013 : one-hot position LED
 * SWE-REQ-014 : alter LED only on valid event
 * SWE-REQ-039 : indicate position
 */
void led_status_set_position(uint8_t position)
{
    if (position == s_current_position_led)
    {
        return;  /* No change – SWE-REQ-014 */
    }

    all_position_leds_off();

    if ((position >= 1U) && (position <= LED_NUM_POSITIONS))
    {
        HAL_GPIO_WritePin(s_pos_leds[position - 1U].port,
                          s_pos_leds[position - 1U].pin,
                          GPIO_PIN_SET);
        s_current_position_led = position;
    }
}

/* SWE-REQ-032 : indicate error state */
void led_status_indicate_error(void)
{
    /* On error: turn off all position LEDs, leave power LED as-is. */
    all_position_leds_off();
}
