#include "led_status_handler.h"
#include "main.h" // For GPIO Ports

void led_status_handler_init(void) {
    // All LEDs OFF at init
    HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS1_GPIO_Port, LED_POS1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS2_GPIO_Port, LED_POS2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS3_GPIO_Port, LED_POS3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS4_GPIO_Port, LED_POS4_Pin, GPIO_PIN_RESET);
}

void led_position_set(uint8_t position) {
    // One-hot: Only activate relevant LED, others off
    HAL_GPIO_WritePin(LED_POS1_GPIO_Port, LED_POS1_Pin, (position == 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS2_GPIO_Port, LED_POS2_Pin, (position == 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS3_GPIO_Port, LED_POS3_Pin, (position == 0x30) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_POS4_GPIO_Port, LED_POS4_Pin, (position == 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void led_indicate_error(void) {
    // For error, blink or activate error LED (example: power LED blink)
    HAL_GPIO_TogglePin(LED_POWER_GPIO_Port, LED_POWER_Pin);
}

void led_power_on(void) {
    HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin, GPIO_PIN_SET);
}
