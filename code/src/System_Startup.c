#include "System_Startup.h"
#include "Command_Parser.h"
#include "Feedback_Processor.h"
#include "Flap_Control_Logic.h"
#include "Motor_Driver.h"
#include "LED_Status_Handler.h"

void System_Startup_Init(void)
{
    Command_Parser_Init();
    Feedback_Processor_Init();
    Motor_Driver_Init();
    LED_Status_Handler_Init();
    Flap_Control_Logic_Init();
}
