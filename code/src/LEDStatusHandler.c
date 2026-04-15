#include "LEDStatusHandler.h"
#include "stm32f4xx_hal.h"

#define POWER_LED_GPIO_PORT GPIOC
#define POWER_LED_PIN GPIO_PIN_13
#define POSITION_LEDS_PORT GPIOB
#define POSITION_LED_PINS {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4}

static const uint16_t position_led_pins[CMD_MAX_POSITIONS] = POSITION_LED_PINS;

void LEDStatusHandler_Init(void) {
    HAL_GPIO_WritePin(POWER_LED_GPIO_PORT, POWER_LED_PIN, GPIO_PIN_SET);
    for (uint8_t i = 0; i < CMD_MAX_POSITIONS; ++i) {
        HAL_GPIO_WritePin(POSITION_LEDS_PORT, position_led_pins[i], GPIO_PIN_RESET);
    }
}

void LEDStatusHandler_SetPowerLED(bool state) {
    HAL_GPIO_WritePin(POWER_LED_GPIO_PORT, POWER_LED_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LEDStatusHandler_SetPositionLED(uint8_t position) {
    for (uint8_t i = 0; i < CMD_MAX_POSITIONS; ++i) {
        HAL_GPIO_WritePin(POSITION_LEDS_PORT, position_led_pins[i], GPIO_PIN_RESET);
    }
    if (position < CMD_MAX_POSITIONS) {
        HAL_GPIO_WritePin(POSITION_LEDS_PORT, position_led_pins[position], GPIO_PIN_SET);
    }
}

void LEDStatusHandler_IndicateError(void) {
    for (uint8_t i = 0; i < CMD_MAX_POSITIONS; ++i) {
        HAL_GPIO_WritePin(POSITION_LEDS_PORT, position_led_pins[i], GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(POWER_LED_GPIO_PORT, POWER_LED_PIN, GPIO_PIN_RESET);
}
