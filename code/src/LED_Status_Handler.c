#include "LED_Status_Handler.h"
#include "stm32f4xx_hal.h"

// Example mappings: assumes 4 positions, 4 LEDs:
#define GREEN_LED_1_GPIO_Port   GPIOA
#define GREEN_LED_1_Pin        GPIO_PIN_0
#define GREEN_LED_2_GPIO_Port   GPIOA
#define GREEN_LED_2_Pin        GPIO_PIN_1
#define GREEN_LED_3_GPIO_Port   GPIOA
#define GREEN_LED_3_Pin        GPIO_PIN_2
#define GREEN_LED_4_GPIO_Port   GPIOA
#define GREEN_LED_4_Pin        GPIO_PIN_3
#define POWER_LED_GPIO_Port     GPIOA
#define POWER_LED_Pin           GPIO_PIN_4
#define ERROR_LED_GPIO_Port     GPIOA
#define ERROR_LED_Pin           GPIO_PIN_5

static void reset_all_leds(void)
{
    HAL_GPIO_WritePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GREEN_LED_2_GPIO_Port, GREEN_LED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GREEN_LED_3_GPIO_Port, GREEN_LED_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GREEN_LED_4_GPIO_Port, GREEN_LED_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_RESET);
}

void LED_Status_Handler_Init(void)
{
    reset_all_leds();
    HAL_GPIO_WritePin(POWER_LED_GPIO_Port, POWER_LED_Pin, GPIO_PIN_SET);
}

void LED_Status_Handler_Set_Position(uint8_t position)
{
    reset_all_leds();
    if(position == 0x10)
        HAL_GPIO_WritePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin, GPIO_PIN_SET);
    else if(position == 0x20)
        HAL_GPIO_WritePin(GREEN_LED_2_GPIO_Port, GREEN_LED_2_Pin, GPIO_PIN_SET);
    else if(position == 0x30)
        HAL_GPIO_WritePin(GREEN_LED_3_GPIO_Port, GREEN_LED_3_Pin, GPIO_PIN_SET);
    else if(position == 0x40)
        HAL_GPIO_WritePin(GREEN_LED_4_GPIO_Port, GREEN_LED_4_Pin, GPIO_PIN_SET);
    // else: do nothing
}

void LED_Status_Handler_Indicate_Error(void)
{
    reset_all_leds();
    HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_SET);
}

void LED_Status_Handler_Set_PowerLed(void)
{
    HAL_GPIO_WritePin(POWER_LED_GPIO_Port, POWER_LED_Pin, GPIO_PIN_SET);
}
