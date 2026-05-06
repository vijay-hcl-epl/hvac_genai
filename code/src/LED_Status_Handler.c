#include "LED_Status_Handler.h"
#include "stm32f4xx_hal.h"

// GPIO assignments must match CubeMX: edit below as per platform HW
#define LED_POWER_GPIO_Port GPIOC
#define LED_POWER_Pin GPIO_PIN_0

static const GPIO_TypeDef* LED_GREEN_PORTS[] = {GPIOC, GPIOC, GPIOC, GPIOC, GPIOC};
static const uint16_t LED_GREEN_PINS[] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5};

void LEDStatusHandler_Init(void)
{
    // Assume GPIOs already initialized via CubeMX
    LEDStatusHandler_SetPowerLED(true);
    for (uint8_t i = 0; i < 5; ++i) {
        HAL_GPIO_WritePin((GPIO_TypeDef*)LED_GREEN_PORTS[i], LED_GREEN_PINS[i], GPIO_PIN_RESET);
    }
}

void LEDStatusHandler_SetPowerLED(bool on)
{
    HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin, (on ? GPIO_PIN_SET : GPIO_PIN_RESET));
}

void LEDStatusHandler_SetGreenLED(uint8_t position)
{
    for (uint8_t i = 0; i < 5; ++i) {
        HAL_GPIO_WritePin((GPIO_TypeDef*)LED_GREEN_PORTS[i], LED_GREEN_PINS[i], (i == position ? GPIO_PIN_SET : GPIO_PIN_RESET));
    }
}

void LEDStatusHandler_IndicateError(void)
{
    // For error, blink power LED or set all Green off
    for (uint8_t i = 0; i < 5; ++i) {
        HAL_GPIO_WritePin((GPIO_TypeDef*)LED_GREEN_PORTS[i], LED_GREEN_PINS[i], GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin, GPIO_PIN_SET);
}
