#include "led_control.h"
#include "stm32f4xx_hal.h"

#define POWER_LED_PIN   GPIO_PIN_7
#define POWER_LED_PORT  GPIOB
static const uint16_t green_led_pins[6] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5 };
static GPIO_TypeDef* green_led_ports[6] = { GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC };

void led_control_init(void)
{
    /* MISRA: Rule 8.7 – Variable only accessed within one function, declared at function scope if possible. Static in file scope okay if accessed by multiple functions. */
    // Assume all LED GPIOs inited in MX_GPIO_Init
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}

void led_update(int8_t position)
{
    for (int i = 0; i < 6; i++)
    {
        HAL_GPIO_WritePin(green_led_ports[i], green_led_pins[i], GPIO_PIN_RESET);
    }
    if ((position >= 0) && (position < 6))
    {
        HAL_GPIO_WritePin(green_led_ports[position], green_led_pins[position], GPIO_PIN_SET);
    }
    HAL_GPIO_WritePin(POWER_LED_PORT, POWER_LED_PIN, GPIO_PIN_SET);
}
