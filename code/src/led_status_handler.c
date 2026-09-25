/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation – power LED, one-hot position LEDs, error.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *         SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * Pin mapping (assumed from STM32F407 Discovery GPIO availability):
 *   Power LED    : PD12  (Green on-board LED)
 *   Position LED1: PD13  (Orange on-board LED) – FULLY_CLOSED
 *   Position LED2: PD14  (Red on-board LED)    – QUARTER_OPEN
 *   Position LED3: PD15  (Blue on-board LED)   – HALF_OPEN
 *   Position LED4: PE2   (External)            – THREE_QTR
 *   Position LED5: PE3   (External)            – FULLY_OPEN
 */

#include "led_status_handler.h"
#include "command_parser.h"   /* CMD_POS_* defines */
#include "stm32f4xx_hal.h"

/* ---- Pin definitions -------------------------------------------------- */

#define LED_POWER_PORT      GPIOD
#define LED_POWER_PIN       GPIO_PIN_12

/** Position LED ports and pins (index 0-4 maps to position 1-5). */
#define LED_POS_COUNT       ((uint8_t)5U)

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} LedPinMap_t;

static const LedPinMap_t s_pos_leds[LED_POS_COUNT] =
{
    { GPIOD, GPIO_PIN_13 },  /* Position 1 – FULLY_CLOSED  */
    { GPIOD, GPIO_PIN_14 },  /* Position 2 – QUARTER_OPEN  */
    { GPIOD, GPIO_PIN_15 },  /* Position 3 – HALF_OPEN     */
    { GPIOE, GPIO_PIN_2  },  /* Position 4 – THREE_QTR     */
    { GPIOE, GPIO_PIN_3  }   /* Position 5 – FULLY_OPEN    */
};

/* ---- Private data ----------------------------------------------------- */

static uint8_t s_current_led_position;

/* ---- Private helpers -------------------------------------------------- */

/**
 * @brief Turn OFF all position LEDs (SWE-REQ-013 one-hot enforcement).
 */
static void Led_AllPositionsOff(void)
{
    uint8_t idx;
    for (idx = 0U; idx < LED_POS_COUNT; idx++)
    {
        HAL_GPIO_WritePin(s_pos_leds[idx].port, s_pos_leds[idx].pin,
                          GPIO_PIN_RESET);
    }
}

/* ---- Public API ------------------------------------------------------- */

void LedStatus_Init(void)
{
    /* GPIO clock enables are assumed done in SystemInit_Run().
     * Here we just set initial output states. */

    /* Power LED ON (SWE-REQ-012). */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);

    /* All position LEDs OFF. */
    Led_AllPositionsOff();
    s_current_led_position = 0U;
}

void LedStatus_SetPosition(uint8_t position)
{
    /* Only update on actual change (SWE-REQ-014). */
    if (position == s_current_led_position)
    {
        return;
    }

    /* One-hot: all OFF first, then target ON (SWE-REQ-013). */
    Led_AllPositionsOff();

    if ((position >= CMD_POS_FULLY_CLOSED) && (position <= CMD_POS_FULLY_OPEN))
    {
        uint8_t idx = position - 1U;
        HAL_GPIO_WritePin(s_pos_leds[idx].port, s_pos_leds[idx].pin,
                          GPIO_PIN_SET);
        s_current_led_position = position;
    }
}

void LedStatus_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

void LedStatus_IndicateError(void)
{
    /* On error: turn OFF all position LEDs, keep power LED ON (SWE-REQ-032). */
    Led_AllPositionsOff();
    s_current_led_position = 0U;
    /* Power LED remains ON to indicate the system is alive. */
}
