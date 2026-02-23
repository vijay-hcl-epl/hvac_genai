#include "uart_handler.h"
#include "flap_manager.h"
#include "motor_control.h"
#include "adc_manager.h"
#include "led_driver.h"
#include "stm32f4xx_hal.h"

int main(void)
{
    HAL_Init();
    UART_Init();
    ADC_Init();
    MOTOR_Init();
    LED_Init();
    LED_PowerOn();
    FLAP_Init();

    int prev_flap = FLAP_GetCurrent();
    LED_UpdatePosition(prev_flap);

    while (1)
    {
        int cmd = UART_GetCommand();
        if (cmd >= 0 && cmd <= 5)
            FLAP_SetTarget(cmd);
        FLAP_Process();
        int cur_flap = FLAP_GetCurrent();
        if (cur_flap != prev_flap)
        {
            LED_UpdatePosition(cur_flap);
            prev_flap = cur_flap;
        }
        HAL_Delay(20);
    }
}
