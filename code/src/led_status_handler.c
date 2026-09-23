/**
 * @file led_status_handler.c
 * @brief LED Status Handler implementation – power LED and one-hot position LED control.
 *
 * Software Unit: LED Status Handler
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL (GPIO)
 *
 * Pin Mapping (configurable via constants):
 *   Power LED   : PD12 (on-board green LED)
 *   Position 1  : PD13 (on-board orange LED)  — reused as position indicators
 *   Position 2  : PD14 (on-board red LED)
 *   Position 3  : PD15 (on-board blue LED)
 *   Position 4  : PE2  (external green LED)
 *   Position 5  : PE3  (external green LED)
 */

#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

/* ---------- Static position-to-pin mapping table [SWE-REQ-030, SWE-REQ-038] ---------- */

/** GPIO Port and Pin pair for each position LED */
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} LedPinMapping_t;

/** Power LED pin */
#define POWER_LED_PORT  GPIOD
#define POWER_LED_PIN   GPIO_PIN_12

/** Position LED mapping table (index 0 = position 1, etc.) */
static const LedPinMapping_t s_PosLedMap[LED_NUM_POSITIONS] =
{
    { GPIOD, GPIO_PIN_13 },  /* Position 1 */
    { GPIOD, GPIO_PIN_14 },  /* Position 2 */
    { GPIOD, GPIO_PIN_15 },  /* Position 3 */
    { GPIOE, GPIO_PIN_2  },  /* Position 4 */
    { GPIOE, GPIO_PIN_3  }   /* Position 5 */
};

/** Current displayed position (0 = none) */
static uint8_t s_CurrentLedPosition = 0U;

/* ---------- Internal helpers -------------------------------------------- */

/**
 * @brief Turn off all position LEDs.
 */
static void LedStatusHandler_AllPositionOff(void)
{
    uint8_t idx;
    for (idx = 0U; idx < LED_NUM_POSITIONS; idx++)
    {
        HAL_GPIO_WritePin(s_PosLedMap[idx].port, s_PosLedMap[idx].pin, GPIO_PIN_RESET);
    }
}

/* ---------- Public API -------------------------------------------------- */

void LedStatusHandler_Init(void)
{
    /* All LEDs off initially */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_RESET);
    LedStatusHandler_AllPositionOff();
    s_CurrentLedPosition = 0U;
}

void LedStatusHandler_SetPowerLed(void)
{
    /* Activate power/initialisation LED [SWE-REQ-012] */
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

void LedStatusHandler_SetLedState(uint8_t pos)
{
    /* Only update on valid position change event [SWE-REQ-014] */
    if ((pos >= 1U) && (pos <= LED_NUM_POSITIONS))
    {
        if (pos != s_CurrentLedPosition)
        {
            /* One-hot: turn all off first, then activate target [SWE-REQ-013] */
            LedStatusHandler_AllPositionOff();
            HAL_GPIO_WritePin(s_PosLedMap[pos - 1U].port,
                              s_PosLedMap[pos - 1U].pin,
                              GPIO_PIN_SET);
            s_CurrentLedPosition = pos;
        }
    }
    else if (pos == 0U)
    {
        /* All position LEDs off */
        LedStatusHandler_AllPositionOff();
        s_CurrentLedPosition = 0U;
    }
    else
    {
        /* Invalid position – no action */
    }
}

void LedStatusHandler_IndicateError(void)
{
    /* Error indication: all position LEDs off, power LED stays ON [SWE-REQ-032] */
    LedStatusHandler_AllPositionOff();
    s_CurrentLedPosition = 0U;
    /* Power LED remains set (do not touch) */
}
