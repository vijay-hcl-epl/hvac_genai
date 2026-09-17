#include "System Startup/Initialization.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "Flap Control Logic.h"
#include "LED Status Handler.h"
#include "Motor Driver.h"
#include "stm32f4xx_hal.h"

static bool System_Startup_Initialization_Done = false;

void System_Startup_Initialization_Init(void)
{
    uint8_t initial_position = 0U;

    HAL_Init();

    Command_Parser_Init();
    Feedback_Processor_Init();
    Motor_Driver_Init();
    LED_Status_Handler_Init();
    Flap_Control_Logic_Init();

    Motor_Driver_StopMotor();
    LED_Status_Handler_SetPowerLed(true);

    Feedback_Processor_Update();
    if (Feedback_Processor_GetPosition(&initial_position) == true)
    {
        LED_Status_Handler_SetLedState(initial_position);
        System_Startup_Initialization_Done = true;
    }
    else
    {
        LED_Status_Handler_IndicateError();
        System_Startup_Initialization_Done = false;
    }
}

bool System_Startup_Initialization_IsInitialized(void)
{
    return System_Startup_Initialization_Done;
}

bool system_init(void)
{
    System_Startup_Initialization_Init();
    return System_Startup_Initialization_IsInitialized();
}
