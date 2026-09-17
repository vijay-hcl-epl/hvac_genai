#include "LED Status Handler.h"
#include "stm32f4xx_hal.h"

#define LED_POSITION_COUNT            (4U)
#define LED_ON                        GPIO_PIN_SET
#define LED_OFF                       GPIO_PIN_RESET
#define LED_POSITION_INVALID          (255U)

typedef struct
{
    GPIO_TypeDef * port;
    uint16_t pin;
} Led_Channel_t;

static const Led_Channel_t position_leds[LED_POSITION_COUNT] =
{
    { GPIOD, GPIO_PIN_13 },
    { GPIOD, GPIO_PIN_14 },
    { GPIOD, GPIO_PIN_15 },
    { GPIOE, GPIO_PIN_0  }
};

static uint8_t led_position_state;

void LED_Status_Handler_Init(void)
{
    uint8_t index = 0U;

    led_position_state = LED_POSITION_INVALID;
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, LED_OFF);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, LED_OFF);
    for (index = 0U; index < LED_POSITION_COUNT; index++)
    {
        HAL_GPIO_WritePin(position_leds[index].port, position_leds[index].pin, LED_OFF);
    }
}

void LED_Status_Handler_Set_Power_Led(uint8_t on)
{
    if (on != 0U)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, LED_ON);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, LED_OFF);
    }
}

void LED_Status_Handler_Set_Led_State(uint8_t position)
{
    uint8_t index = 0U;

    if (position < LED_POSITION_COUNT)
    {
        for (index = 0U; index < LED_POSITION_COUNT; index++)
        {
            if (index == position)
            {
                HAL_GPIO_WritePin(position_leds[index].port, position_leds[index].pin, LED_ON);
            }
            else
            {
                HAL_GPIO_WritePin(position_leds[index].port, position_leds[index].pin, LED_OFF);
            }
        }
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, LED_OFF);
        led_position_state = position;
    }
}

void LED_Status_Handler_Indicate_Error(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, LED_ON);
}

uint8_t LED_Status_Handler_Get_Position_State(void)
{
    return led_position_state;
}
