#include "hardware_abstraction_layer.h"

static HAL_PeripheralConfig g_hal_config;

void HAL_InitPeripherals(const HAL_PeripheralConfig* config) {
    g_hal_config = *config;
    // Initialization handled by STM32CubeMX, ensure config pointers are set
}

int HAL_SetMotorPosition(int position) {
    // Dummy implementation: Map position to PWM duty or GPIO
    // Actual mapping handled by higher level
    return 0; // Always return success for stub
}

int HAL_ReadFlapPosition(void) {
    // Read ADC, return value
    uint32_t value = 0;
    if (HAL_ADC_PollForConversion(g_hal_config.hadc, 10) == HAL_OK) {
        value = HAL_ADC_GetValue(g_hal_config.hadc);
    }
    return (int)value;
}

void HAL_SetLED(uint8_t led_idx, uint8_t state) {
    if (led_idx < 6) {
        HAL_GPIO_WritePin(g_hal_config.gpio_port_led, g_hal_config.gpio_pins_led[led_idx], state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void HAL_AllLEDOff(void) {
    for (int i = 0; i < 6; ++i) {
        HAL_SetLED(i, 0);
    }
}
