#include "led_status_handler.h"
#include "stm32f4xx_hal.h"

#define POWER_LED_GPIO_Port GPIOB
#define POWER_LED_Pin GPIO_PIN_0
static const struct { GPIO_TypeDef *port; uint16_t pin; } position_leds[] = {
    {GPIOB, GPIO_PIN_1}, {GPIOB, GPIO_PIN_2}, {GPIOB, GPIO_PIN_3}, {GPIOB, GPIO_PIN_4}
};

void led_status_handler_init(void) {
    HAL_GPIO_WritePin(POWER_LED_GPIO_Port, POWER_LED_Pin, GPIO_PIN_SET);
    for (uint8_t i = 0; i < sizeof(position_leds)/sizeof(position_leds[0]); ++i) {
        HAL_GPIO_WritePin(position_leds[i].port, position_leds[i].pin, GPIO_PIN_RESET);
    }
}

void led_set_power_led(bool on) {
    HAL_GPIO_WritePin(POWER_LED_GPIO_Port, POWER_LED_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void led_set_position(uint8_t position) {
    for (uint8_t i = 0; i < sizeof(position_leds)/sizeof(position_leds[0]); ++i) {
        HAL_GPIO_WritePin(position_leds[i].port, position_leds[i].pin, (i == position) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void led_indicate_error(void) {
    // Indicate error by fast-blink or alternate pattern, simple implementation here:
    for (uint8_t i = 0; i < sizeof(position_leds)/sizeof(position_leds[0]); ++i) {
        HAL_GPIO_TogglePin(position_leds[i].port, position_leds[i].pin);
    }
}
