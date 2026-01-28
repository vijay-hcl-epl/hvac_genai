/**
 @file hw_abstraction.c
 @brief Hardware Abstraction Layer implementation.
 @responsibility: Implements platform abstraction for UART, ADC, PWM, GPIO/LED for STM32F407G-DISC1. No application logic permitted here.
*/
#include "hw_abstraction.h"
#include <stdint.h>
#include <stdbool.h>

void HW_UART_Init(void)
{
    /* User to implement actual HAL UART initialization here */
}

bool HW_UART_Receive(uint8_t *rxByte)
{
    /* User to implement actual HAL UART receive non-blocking. Returns true if byte received. */
    return false;
}

void HW_UART_IRQHandler(void)
{
    /* IRQ Handler stub if needed */
}

void HW_ADC_Init(void)
{
    /* User to implement actual HAL ADC initialization here */
}

uint16_t HW_ADC_Read(void)
{
    /* User to implement actual HAL ADC read here */
    return 0U;
}

void HW_GPIO_Init(void)
{
    /* User to implement actual HAL GPIO initialization here */
}

void HW_LED_Set(uint8_t led_index, bool state)
{
    /* User to implement LED drive here, e.g., via HAL_GPIO_WritePin. Index guards should apply. */
}

void HW_PWM_Init(void)
{
    /* User to implement HAL timer/PWM initialization here */
}

void HW_Motor_SetDirection(MotorDirection_t direction)
{
    /* User to implement DIrection GPIO logic here */
}

void HW_Motor_Enable(bool enable)
{
    /* User to implement timer/PWM ON/OFF logic here */
}
