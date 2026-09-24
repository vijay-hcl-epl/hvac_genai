/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation.
 *
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * STM32F407G-DISC1 on-board LEDs used for demonstration:
 *   Power LED  : PD12 (Green)
 *   Position 1 : PD13 (Orange)
 *   Position 2 : PD14 (Red)
 *   Position 3 : PD15 (Blue)
 *   Position 4 : PC0  (External green LED 1)
 *   Position 5 : PC1  (External green LED 2)
 *
 * In a production design, all 5 position LEDs would be green;
 * here we use available GPIOs for prototype demonstration.
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- GPIO Pin / Port mapping [SWE-REQ-018] ---- */

/** Power LED */
#define LED_POWER_PORT     GPIOD
#define LED_POWER_PIN      GPIO_PIN_12

/** Position LED definitions (1..5) */
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} LedPinMap_t;

static const LedPinMap_t posLedMap[LED_NUM_POSITIONS] =
{
    { GPIOD, GPIO_PIN_13 },   /* Position 1 */
    { GPIOD, GPIO_PIN_14 },   /* Position 2 */
    { GPIOD, GPIO_PIN_15 },   /* Position 3 */
    { GPIOC, GPIO_PIN_0  },   /* Position 4 */
    { GPIOC, GPIO_PIN_1  }    /* Position 5 */
};

/* ---- Module static data [SWE-REQ-036] ---- */
static uint8_t s_currentLedPos;  /* 0 = none, 1..5 = active position */

/* ---- Private helpers ---- */

/**
 * @brief Turn off all position LEDs.
 */
static void Led_AllPositionsOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(posLedMap[i].port, posLedMap[i].pin, GPIO_PIN_RESET);
    }
}

/* ---- Public API ---- */

void LedStatus_Init(void)
{
    Led_AllPositionsOff();
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_RESET);
    s_currentLedPos = 0U;
}

void LedStatus_SetPowerLed(void)
{
    /* [SWE-REQ-012] Power LED ON */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

void LedStatus_SetPosition(uint8_t position)
{
    /* Only update on actual change [SWE-REQ-014] */
    if (position == s_currentLedPos)
    {
        return;
    }

    /* One-hot: all off first, then selected on [SWE-REQ-013] */
    Led_AllPositionsOff();

    if ((position >= 1U) && (position <= LED_NUM_POSITIONS))
    {
        HAL_GPIO_WritePin(posLedMap[position - 1U].port,
                          posLedMap[position - 1U].pin,
                          GPIO_PIN_SET);
        s_currentLedPos = position;
    }
    else
    {
        /* Invalid position: all off */
        s_currentLedPos = 0U;
    }
}

void LedStatus_IndicateError(void)
{
    /* [SWE-REQ-032] Error indication: turn off all position LEDs */
    Led_AllPositionsOff();
    s_currentLedPos = 0U;
    /* Power LED remains on to show the system is alive */
}
