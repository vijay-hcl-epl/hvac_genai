/**
 * @file led_status_handler.c
 * @brief LED Status Handler Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018,
 *   SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * Pin Assignment (assumed, configurable via the tables below):
 *   Power LED    : PD12 (Green on-board LED)
 *   Position LED1: PE2
 *   Position LED2: PE3
 *   Position LED3: PE4
 *   Position LED4: PE5
 *   Position LED5: PE6
 *
 * [SWE-REQ-018, SWE-REQ-038]
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Static configuration data ---------- */
/* Position-to-LED GPIO mapping table [SWE-REQ-027, SWE-REQ-030, SWE-REQ-038] */

/** GPIO port for each position LED (index 0 = position 1) */
static GPIO_TypeDef* const s_posLedPort[LED_NUM_POSITIONS] =
{
    GPIOE,  /* Position 1 */
    GPIOE,  /* Position 2 */
    GPIOE,  /* Position 3 */
    GPIOE,  /* Position 4 */
    GPIOE   /* Position 5 */
};

/** GPIO pin for each position LED */
static const uint16_t s_posLedPin[LED_NUM_POSITIONS] =
{
    GPIO_PIN_2,   /* Position 1 */
    GPIO_PIN_3,   /* Position 2 */
    GPIO_PIN_4,   /* Position 3 */
    GPIO_PIN_5,   /* Position 4 */
    GPIO_PIN_6    /* Position 5 */
};

/** Power LED port and pin */
#define POWER_LED_PORT  GPIOD
#define POWER_LED_PIN   GPIO_PIN_12

/* ---------- Static module data ---------- */
/* [SWE-REQ-036, SWE-REQ-038] */

/** Bitmask representing current position LED state (for tracking) */
static uint8_t s_currentLedPosition = 0U;

/* ---------- Private helpers ---------- */

/**
 * @brief Turn OFF all position LEDs.
 *        [SWE-REQ-013 – one-hot enforcement helper]
 */
static void AllPositionLedsOff(void)
{
    uint8_t i;
    for (i = 0U; i < LED_NUM_POSITIONS; i++)
    {
        HAL_GPIO_WritePin(s_posLedPort[i], s_posLedPin[i], GPIO_PIN_RESET);
    }
}

/* ---------- Public API ---------- */

/**
 * @brief Initialise the LED Status Handler unit.
 *        All position LEDs OFF; power LED ON.
 *        [SWE-REQ-012, SWE-REQ-020]
 */
void LedStatusHandler_Init(void)
{
    AllPositionLedsOff();
    s_currentLedPosition = 0U;

    /* Power LED ON [SWE-REQ-012] */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

/**
 * @brief Set the power/initialisation LED ON.
 *        [SWE-REQ-012]
 */
void LedStatusHandler_SetPowerLed(void)
{
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

/**
 * @brief Update the position LED to reflect a valid flap position.
 *
 * One-hot enforcement: all position LEDs are turned OFF first, then
 * the LED corresponding to @p position is turned ON.
 *
 * @param position  1..LED_NUM_POSITIONS (0 or out-of-range → all OFF).
 *        [SWE-REQ-013, SWE-REQ-014, SWE-REQ-039]
 */
void LedStatusHandler_SetLedState(uint8_t position)
{
    /* Turn off all first [SWE-REQ-013 – at most one ON] */
    AllPositionLedsOff();

    if ((position >= 1U) && (position <= LED_NUM_POSITIONS))
    {
        uint8_t idx = position - 1U;
        HAL_GPIO_WritePin(s_posLedPort[idx], s_posLedPin[idx], GPIO_PIN_SET);
        s_currentLedPosition = position;
    }
    else
    {
        s_currentLedPosition = 0U;
    }
}

/**
 * @brief Indicate an error condition – all position LEDs OFF (safe).
 *        [SWE-REQ-032]
 */
void LedStatusHandler_IndicateError(void)
{
    AllPositionLedsOff();
    s_currentLedPosition = 0U;
}
