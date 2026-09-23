/**
 * @file    led_status_handler.c
 * @brief   LED Status Handler software unit – implementation.
 *
 * Traceability:
 *   SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021,
 *   SWE-REQ-036, SWE-REQ-039.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL.
 *
 * Pin Mapping (assumed for STM32F407G-DISC1 + external LEDs):
 *   Power LED    : PD12 (on-board green LED)
 *   Position 0   : PE7
 *   Position 1   : PE8
 *   Position 2   : PE9
 *   Position 3   : PE10
 *   Position 4   : PE11
 */

/* ---- Includes ------------------------------------------------------- */
#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---- Private Constants / Pin Map (SWE-REQ-018, SWE-REQ-038) -------- */

/** @brief Power / run LED (on-board green, PD12). */
#define LED_POWER_PORT     GPIOD
#define LED_POWER_PIN      GPIO_PIN_12

/** @brief Position LED GPIO port (all on GPIOE for this board). */
#define LED_POS_PORT       GPIOE

/** @brief Position LED pin table (statically declared, SWE-REQ-038). */
static const uint16_t s_posLedPins[LED_NUM_POSITIONS] =
{
    GPIO_PIN_7,   /* Position 0 */
    GPIO_PIN_8,   /* Position 1 */
    GPIO_PIN_9,   /* Position 2 */
    GPIO_PIN_10,  /* Position 3 */
    GPIO_PIN_11   /* Position 4 */
};

/* ---- Static Data (SWE-REQ-036) ------------------------------------- */

/** @brief Currently displayed position (used to avoid redundant writes,
 *         SWE-REQ-014). */
static uint8_t s_currentLedPos;
static uint8_t s_ledInitialised;

/* ---- Private Helpers ------------------------------------------------ */

/**
 * @brief  Turn OFF all position LEDs.
 */
static void LED_AllPositionOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(LED_POS_PORT, s_posLedPins[i], GPIO_PIN_RESET);
    }
}

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020] */
void LedStatus_Init(void)
{
    /* All position LEDs OFF. */
    LED_AllPositionOff();

    /* Power LED OFF initially (will be set by SystemInit after checks). */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_RESET);

    s_currentLedPos  = 0xFFU; /* Invalid sentinel. */
    s_ledInitialised = 1U;
}

/* [SWE-REQ-012] */
void LedStatus_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
}

/* [SWE-REQ-013, SWE-REQ-014, SWE-REQ-039] */
void LedStatus_SetPosition(uint8_t position)
{
    if (position >= LED_NUM_POSITIONS)
    {
        return; /* Out-of-range guard. */
    }

    /* Only update on change (SWE-REQ-014). */
    if (position == s_currentLedPos)
    {
        return;
    }

    /* One-hot: all OFF, then selected ON (SWE-REQ-013). */
    LED_AllPositionOff();
    HAL_GPIO_WritePin(LED_POS_PORT, s_posLedPins[position], GPIO_PIN_SET);
    s_currentLedPos = position;
}

/* [SWE-REQ-032] */
void LedStatus_IndicateError(void)
{
    /* Turn OFF all position LEDs; power LED stays ON. */
    LED_AllPositionOff();
    s_currentLedPos = 0xFFU;
}
