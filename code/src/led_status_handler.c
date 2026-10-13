/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation.
 *
 * Software Unit : LED Status Handler
 * Traces        : SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *                 SWE-REQ-021, SWE-REQ-039
 * Platform      : STM32F407G-DISC1, GPIO-based LEDs
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Platform GPIO mapping (env-setup: GPIO for LED control) ---- */
/*
 * STM32F407G-DISC1 on-board LEDs:
 *   PD12 – Green   (used as Power / Initialization LED)
 *   PD13 – Orange  (position 0 indicator – Fully closed)
 *   PD14 – Red     (position 1 indicator – 25%)
 *   PD15 – Blue    (position 2 indicator – 50%)
 * External LEDs (directly driven GPIOs):
 *   PE0  – Green   (position 3 indicator – 75%)
 *   PE1  – Green   (position 4 indicator – Fully open)
 *
 * All active-high.
 */

/** Power LED */
#define LED_POWER_PORT  GPIOD
#define LED_POWER_PIN   GPIO_PIN_12

/** Position indicator LED table – index matches logical position 0..4 */
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} LedGpioMap_t;

static const LedGpioMap_t posLedMap[LED_NUM_POSITION_LEDS] =
{
    { GPIOD, GPIO_PIN_13 },   /* Position 0 – Fully closed */
    { GPIOD, GPIO_PIN_14 },   /* Position 1 – 25 %         */
    { GPIOD, GPIO_PIN_15 },   /* Position 2 – 50 %         */
    { GPIOE, GPIO_PIN_0  },   /* Position 3 – 75 %         */
    { GPIOE, GPIO_PIN_1  }    /* Position 4 – Fully open   */
};

/* ---------- Static data (SWE-REQ-036, SWE-REQ-038) --------------------- */
static uint8_t currentLedPos;  /* Last indicated position */

/* ---------- Private helpers -------------------------------------------- */

/**
 * @brief Turn all position LEDs OFF.
 * Traces: SWE-REQ-013 (one-hot enforcement)
 */
static void AllPositionLedsOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITION_LEDS; i++)
    {
        HAL_GPIO_WritePin(posLedMap[i].port, posLedMap[i].pin, GPIO_PIN_RESET);
    }
}

/* ---------- Public API ------------------------------------------------- */

void LedStatus_Init(void)
{
    currentLedPos = 0xFFU;  /* Force first update */
    AllPositionLedsOff();
    /* Power LED ON at startup (SWE-REQ-012) */
    LedStatus_SetPowerLed();
}

void LedStatus_SetPosition(uint8_t position)
{
    /* Only alter LEDs on actual change (SWE-REQ-014) */
    if ((position < LED_NUM_POSITION_LEDS) && (position != currentLedPos))
    {
        AllPositionLedsOff();  /* One-hot: SWE-REQ-013 */
        HAL_GPIO_WritePin(posLedMap[position].port,
                          posLedMap[position].pin,
                          GPIO_PIN_SET);
        currentLedPos = position;
    }
}

void LedStatus_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

void LedStatus_IndicateError(void)
{
    /*
     * Error indication: all position LEDs OFF, power LED stays ON.
     * SWE-REQ-032: safe idle – no movement, status LEDs unchanged beyond
     * clearing position indicator.
     */
    AllPositionLedsOff();
    currentLedPos = 0xFFU;
}
