#include "status_indicator.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

// LED GPIO definitions (symbolic, match Cube config)
#define POWER_LED_PORT     GPIOC
#define POWER_LED_PIN      GPIO_PIN_0
#define NUM_POS_LEDS       6
static const GPIO_TypeDef* POS_LED_PORTS[NUM_POS_LEDS] = {GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC};
static const uint16_t POS_LED_PINS[NUM_POS_LEDS] = {GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6};

void StatusIndicator_Init(void)
{
    // User should initialize GPIOs in board setup.
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
    for (int i = 0; i < NUM_POS_LEDS; ++i) {
        HAL_GPIO_WritePin(POS_LED_PORTS[i], POS_LED_PINS[i], GPIO_PIN_RESET);
    }
}

void StatusIndicator_Update(uint8_t logical_position, bool powered)
{
    if (powered) {
        HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_RESET);
    }
    for (int i = 0; i < NUM_POS_LEDS; ++i) {
        if (i == logical_position && powered) {
            HAL_GPIO_WritePin(POS_LED_PORTS[i], POS_LED_PINS[i], GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(POS_LED_PORTS[i], POS_LED_PINS[i], GPIO_PIN_RESET);
        }
    }
}
