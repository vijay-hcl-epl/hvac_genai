#include "led_driver.h"
#include "stm32f4xx_hal.h"
#define LED_PWR_PIN GPIO_PIN_0 // e.g., PC0
#define LED_PWR_PORT GPIOC
#define LED_POS_PINS (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6) // example positions
#define LED_POS_PORT GPIOC

void LED_Init(void){}

void LED_PowerOn(void)
{
    HAL_GPIO_WritePin(LED_PWR_PORT, LED_PWR_PIN, GPIO_PIN_SET);
}

void LED_UpdatePosition(int pos)
{
    uint16_t all_pins[6] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6};
    for (int i = 0; i < 6; ++i)
        HAL_GPIO_WritePin(LED_POS_PORT, all_pins[i], (i == pos) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
