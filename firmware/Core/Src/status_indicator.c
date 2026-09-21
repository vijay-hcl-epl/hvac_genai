#include "status_indicator.h"
#include "stm32f4xx_hal.h"

static const GPIO_TypeDef * const LED_POWER_PORT = GPIOC;
static const uint16_t LED_POWER_PIN = GPIO_PIN_0;
static const GPIO_TypeDef * const LED_POS_PORT = GPIOC;

static const uint16_t s_led_pos_pins[STATUS_INDICATOR_NUM] = {
    GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5
};

void StatusIndicator_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = LED_POWER_PIN | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Turn power LED ON, all position LEDs off */
    HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
    for (uint8_t i = 0U; i < (uint8_t)STATUS_INDICATOR_NUM; ++i)
    {
        HAL_GPIO_WritePin(LED_POS_PORT, s_led_pos_pins[i], GPIO_PIN_RESET);
    }
}

void StatusIndicator_Update(const uint8_t position_valid, const uint8_t logical_position)
{
    /* Turn OFF all position LEDs */
    for (uint8_t i = 0U; i < (uint8_t)STATUS_INDICATOR_NUM; ++i)
    {
        HAL_GPIO_WritePin(LED_POS_PORT, s_led_pos_pins[i], GPIO_PIN_RESET);
    }

    /* Position 0 → no green LED */
    if ((position_valid != 0U) && (logical_position > 0U) &&
        (logical_position <= (uint8_t)STATUS_INDICATOR_NUM))
    {
        /* position 1 → LED 0
           position 2 → LED 1
           ...
           position 5 → LED 4 */
        HAL_GPIO_WritePin(LED_POS_PORT,
                          s_led_pos_pins[(uint8_t)(logical_position - 1U)],
                          GPIO_PIN_SET);
    }
}

void StatusIndicator_SetPowerLED(uint8_t onoff)
{
    /* 1 = ON, 0 = OFF */
    if (onoff != 0U)
    {
        HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_POWER_PORT, LED_POWER_PIN, GPIO_PIN_RESET);
    }
}