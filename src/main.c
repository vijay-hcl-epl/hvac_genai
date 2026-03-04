/*
 * HVAC Flap Actuator Prototype - Main Implementation Stub
 * Derived from SW LLD and architecture for ASPICE demonstration
 * Platform: STM32F407G-DISC1 | STM32CubeIDE | STM32 HAL
 */
#include "stm32f4xx_hal.h"
#include "user_cmd.h"
#include "pos_ctrl.h"
#include "motor_ctrl.h"
#include "feedback_adc.h"
#include "status_led.h"
#include "system_cfg.h"

void System_Init(void) {
    HAL_Init();
    UART_Init();
    ADC_Init();
    GPIO_Init();
    PWM_Init();
    LED_SetPower(1);
    LED_UpdatePosition(Feedback_Adc_Read());
    Motor_Control_Enable(0);
}

int main(void)
{
    System_Init();
    while (1) {
        // Poll or receive UART command
        uint8_t cmd;
        if (UART_ReceiveNonBlocking(&cmd)) {
            UART_UserCmd_ReceiveHandler(cmd);
        }
        POSCTRL_HandleTargetMove();
        LED_UpdatePosition(Feedback_Adc_Read());
        // Delay or loop as per scheduler
    }
}
