#include "System_Startup.h"
#include "Flap_Control_Logic.h"
#include "stm32f4xx_hal.h"

extern void SystemClock_Config(void);
extern void MX_GPIO_Init(void);
extern void MX_USART2_UART_Init(void);
extern void MX_ADC1_Init(void);
extern void MX_TIM3_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM3_Init();

    System_Startup_Init();

    while(1)
    {
        Flap_Control_Logic_Task();
        HAL_Delay(10); // Polling interval, not timing constraint
    }
}
