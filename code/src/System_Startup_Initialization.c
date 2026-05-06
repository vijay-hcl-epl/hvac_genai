#include "System_Startup_Initialization.h"
#include "Command_Parser.h"
#include "Flap_Control_Logic.h"
#include "Motor_Driver.h"
#include "Feedback_Processor.h"
#include "LED_Status_Handler.h"

void SystemStartupInitialization_InitAll(void)
{
    // All STM32 HAL/clock/device init assumed called by main.c (CubeMX)
    CommandParser_Init();
    FeedbackProcessor_Init();
    MotorDriver_Init();
    LEDStatusHandler_Init();
    FlapControlLogic_Init();
}
