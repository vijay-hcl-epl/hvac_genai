#include "LED Status Handler.h"
#include "stm32f4xx_hal.h"

#define LED_POWER_PORT GPIOB
#define LED_POWER_PIN  GPIO_PIN_0
#define LED_POS0_PORT  GPIOD
#define LED_POS0_PIN   GPIO_PIN_13
#define LED_POS1_PORT  GPIOD
#define LED_POS1_PIN   GPIO_PIN_14
#define LED_POS2_PORT  GPIOD
#define LED_POS2_PIN   GPIO_PIN_15
#define LED_POS3_PORT  GPIOC
#define LED_POS3_PIN   GPIO_PIN_7

static uint8_t led_state;

static void LEDStatusHandler_ClearPositionLeds(void)
{
    HAL_GPIO_WritePin(LED_POS0_PORT, LED_POS0_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS1_PORT, LED_POS1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS2_PORT, LED_POS2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS3_PORT, LED_POS3_PIN, GPIO_PIN_RESET);
}

void LEDStatusHandler_Init(void)
{
    led_state = 0U;
    LEDStatusHandler_ClearPositionLeds();
    LEDStatusHandler_SetPowerLed();
}

void LEDStatusHandler_SetPowerLed(void)
{
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
    led_state |= 0x80U;
}

void LEDStatusHandler_SetLedState(uint8_t position)
{
    LEDStatusHandler_ClearPositionLeds();

    if (position == 0U)
    {
        HAL_GPIO_WritePin(LED_POS0_PORT, LED_POS0_PIN, GPIO_PIN_SET);
        led_state = 0x81U;
    }
    else if (position == 1U)
    {
        HAL_GPIO_WritePin(LED_POS1_PORT, LED_POS1_PIN, GPIO_PIN_SET);
        led_state = 0x82U;
    }
    else if (position == 2U)
    {
        HAL_GPIO_WritePin(LED_POS2_PORT, LED_POS2_PIN, GPIO_PIN_SET);
        led_state = 0x84U;
    }
    else if (position == 3U)
    {
        HAL_GPIO_WritePin(LED_POS3_PORT, LED_POS3_PIN, GPIO_PIN_SET);
        led_state = 0x88U;
    }
    else
    {
        led_state = 0x80U;
    }
}

void LEDStatusHandler_IndicateError(void)
{
    LEDStatusHandler_ClearPositionLeds();
    LEDStatusHandler_SetPowerLed();
    led_state = 0x80U;
}

uint8_t LEDStatusHandler_GetCurrentState(void)
{
    return led_state;
}
