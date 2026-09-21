#include "LED Status Handler.h"
#include "stm32f4xx_hal.h"

/* Status LED handling with one-hot green position indication.
 * Traces: SWE-REQ-012, SWE-REQ-013, SWE-REQ-014, SWE-REQ-018, SWE-REQ-021, SWE-REQ-039.
 */

#define LED_STATUS_POWER_GPIO_PORT      GPIOD
#define LED_STATUS_POWER_GPIO_PIN       GPIO_PIN_12
#define LED_STATUS_POS0_GPIO_PORT       GPIOD
#define LED_STATUS_POS0_GPIO_PIN        GPIO_PIN_13
#define LED_STATUS_POS1_GPIO_PORT       GPIOD
#define LED_STATUS_POS1_GPIO_PIN        GPIO_PIN_14
#define LED_STATUS_POS2_GPIO_PORT       GPIOD
#define LED_STATUS_POS2_GPIO_PIN        GPIO_PIN_15
#define LED_STATUS_POS3_GPIO_PORT       GPIOE
#define LED_STATUS_POS3_GPIO_PIN        GPIO_PIN_0
#define LED_STATUS_ERROR_GPIO_PORT      GPIOE
#define LED_STATUS_ERROR_GPIO_PIN       GPIO_PIN_1

typedef struct
{
    GPIO_TypeDef * port;
    uint16_t pin;
    Hvac_FlapPosition_t position;
} LedStatus_MapEntry_t;

static const LedStatus_MapEntry_t LedStatus_PositionMap[] =
{
    { LED_STATUS_POS0_GPIO_PORT, LED_STATUS_POS0_GPIO_PIN, HVAC_FLAP_POSITION_FACE },
    { LED_STATUS_POS1_GPIO_PORT, LED_STATUS_POS1_GPIO_PIN, HVAC_FLAP_POSITION_BI_LEVEL },
    { LED_STATUS_POS2_GPIO_PORT, LED_STATUS_POS2_GPIO_PIN, HVAC_FLAP_POSITION_FOOT },
    { LED_STATUS_POS3_GPIO_PORT, LED_STATUS_POS3_GPIO_PIN, HVAC_FLAP_POSITION_DEFROST }
};

static uint8_t LedStatus_CurrentBits = 0U;
static LedStatus_Mode_t LedStatus_CurrentMode = LED_STATUS_NORMAL;

static void LedStatus_AllPositionLedsOff(void)
{
    uint32_t index;

    for (index = 0U; index < (sizeof(LedStatus_PositionMap) / sizeof(LedStatus_PositionMap[0])); index++)
    {
        HAL_GPIO_WritePin(LedStatus_PositionMap[index].port, LedStatus_PositionMap[index].pin, GPIO_PIN_RESET);
    }
}

void LedStatusHandler_Init(void)
{
    LedStatus_CurrentBits = 0U;
    LedStatus_CurrentMode = LED_STATUS_NORMAL;
    LedStatus_AllPositionLedsOff();
    HAL_GPIO_WritePin(LED_STATUS_ERROR_GPIO_PORT, LED_STATUS_ERROR_GPIO_PIN, GPIO_PIN_RESET);
}

void LedStatusHandler_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_STATUS_POWER_GPIO_PORT, LED_STATUS_POWER_GPIO_PIN, GPIO_PIN_SET);
}

void LedStatusHandler_SetLedState(Hvac_FlapPosition_t pos)
{
    uint32_t index;
    uint8_t bits = 0U;

    LedStatus_AllPositionLedsOff();
    HAL_GPIO_WritePin(LED_STATUS_ERROR_GPIO_PORT, LED_STATUS_ERROR_GPIO_PIN, GPIO_PIN_RESET);

    for (index = 0U; index < (sizeof(LedStatus_PositionMap) / sizeof(LedStatus_PositionMap[0])); index++)
    {
        if (LedStatus_PositionMap[index].position == pos)
        {
            HAL_GPIO_WritePin(LedStatus_PositionMap[index].port, LedStatus_PositionMap[index].pin, GPIO_PIN_SET);
            bits = (uint8_t)(1UL << index);
            break;
        }
    }

    LedStatus_CurrentBits = bits;
    LedStatus_CurrentMode = LED_STATUS_NORMAL;
}

void LedStatusHandler_IndicateError(void)
{
    HAL_GPIO_WritePin(LED_STATUS_ERROR_GPIO_PORT, LED_STATUS_ERROR_GPIO_PIN, GPIO_PIN_SET);
    LedStatus_CurrentMode = LED_STATUS_ERROR;
}

uint8_t LedStatusHandler_GetLedBits(void)
{
    return LedStatus_CurrentBits;
}

LedStatus_Mode_t LedStatusHandler_GetMode(void)
{
    return LedStatus_CurrentMode;
}
