#include "System_Startup_Initialization.h"
#include "Flap_Control_Logic.h"
#include "Command_Parser.h"
#include "stm32f4xx_hal.h"

// HAL/clock init must be done before main loop (CubeMX)
int main(void)
{
    HAL_Init();
    SystemClock_Config(); // Must be defined elsewhere (usually CubeMX)
    MX_GPIO_Init();       // Must be defined elsewhere
    MX_USART2_UART_Init();// Must be defined elsewhere
    MX_ADC1_Init();       // Must be defined elsewhere
    MX_TIM3_Init();       // Must be defined elsewhere

    SystemStartupInitialization_InitAll();

    while (1)
    {
        CommandParser_ProcessUART();
        FlapControlLogic_Task();
        // Optionally: add watchdog/task checsk here
    }
}

// Dummy stubs (to be replaced by CubeMX generated code)
void SystemClock_Config(void) {}
void MX_GPIO_Init(void) {}
void MX_USART2_UART_Init(void) {}
void MX_ADC1_Init(void) {}
void MX_TIM3_Init(void) {}
