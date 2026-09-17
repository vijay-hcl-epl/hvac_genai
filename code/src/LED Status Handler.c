#include "LED Status Handler.h"
#include "stm32f4xx_hal.h"

#ifndef HVAC_LED_POWER_PORT
#define HVAC_LED_POWER_PORT GPIOD
#endif
#ifndef HVAC_LED_POWER_PIN
#define HVAC_LED_POWER_PIN GPIO_PIN_12
#endif
#ifndef HVAC_LED_POS0_PORT
#define HVAC_LED_POS0_PORT GPIOD
#endif
#ifndef HVAC_LED_POS0_PIN
#define HVAC_LED_POS0_PIN GPIO_PIN_13
#endif
#ifndef HVAC_LED_POS1_PORT
#define HVAC_LED_POS1_PORT GPIOD
#endif
#ifndef HVAC_LED_POS1_PIN
#define HVAC_LED_POS1_PIN GPIO_PIN_14
#endif
#ifndef HVAC_LED_POS2_PORT
#define HVAC_LED_POS2_PORT GPIOD
#endif
#ifndef HVAC_LED_POS2_PIN
#define HVAC_LED_POS2_PIN GPIO_PIN_15
#endif
#ifndef HVAC_LED_POS3_PORT
#define HVAC_LED_POS3_PORT GPIOA
#endif
#ifndef HVAC_LED_POS3_PIN
#define HVAC_LED_POS3_PIN GPIO_PIN_0
#endif

typedef struct
{
    GPIO_TypeDef * port;
    uint16_t pin;
} LED_Status_Handler_PinMapType;

static const LED_Status_Handler_PinMapType LED_Status_Handler_PositionLedMap[4U] =
{
    { HVAC_LED_POS0_PORT, HVAC_LED_POS0_PIN },
    { HVAC_LED_POS1_PORT, HVAC_LED_POS1_PIN },
    { HVAC_LED_POS2_PORT, HVAC_LED_POS2_PIN },
    { HVAC_LED_POS3_PORT, HVAC_LED_POS3_PIN }
};

static uint8_t LED_Status_Handler_LedBits = 0U;

static void LED_Status_Handler_ClearPositionLeds(void)
{
    uint8_t index = 0U;

    for (index = 0U; index < 4U; index++)
    {
        HAL_GPIO_WritePin(LED_Status_Handler_PositionLedMap[index].port,
                          LED_Status_Handler_PositionLedMap[index].pin,
                          GPIO_PIN_RESET);
    }
    LED_Status_Handler_LedBits &= (uint8_t)0xF0U;
}

void LED_Status_Handler_Init(void)
{
    LED_Status_Handler_LedBits = 0U;
    LED_Status_Handler_ClearPositionLeds();
    LED_Status_Handler_SetPowerLed(false);
}

void LED_Status_Handler_SetPowerLed(bool on)
{
    HAL_GPIO_WritePin(HVAC_LED_POWER_PORT,
                      HVAC_LED_POWER_PIN,
                      (on == true) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    if (on == true)
    {
        LED_Status_Handler_LedBits |= (uint8_t)0x80U;
    }
    else
    {
        LED_Status_Handler_LedBits &= (uint8_t)0x7FU;
    }
}

void LED_Status_Handler_SetLedState(uint8_t position)
{
    if (position < 4U)
    {
        LED_Status_Handler_ClearPositionLeds();
        HAL_GPIO_WritePin(LED_Status_Handler_PositionLedMap[position].port,
                          LED_Status_Handler_PositionLedMap[position].pin,
                          GPIO_PIN_SET);
        LED_Status_Handler_LedBits = (uint8_t)((LED_Status_Handler_LedBits & 0xF0U) | (1U << position));
    }
}

void LED_Status_Handler_IndicateError(void)
{
    LED_Status_Handler_ClearPositionLeds();
    LED_Status_Handler_LedBits |= (uint8_t)0x40U;
}

uint8_t LED_Status_Handler_GetLedBits(void)
{
    return LED_Status_Handler_LedBits;
}
