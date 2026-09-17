#include "System Startup/Initialization.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "Flap Control Logic.h"
#include "Motor Driver.h"
#include "LED Status Handler.h"

#define SYSTEM_INIT_NOT_DONE          (0U)
#define SYSTEM_INIT_DONE              (1U)

static uint8_t system_init_status = SYSTEM_INIT_NOT_DONE;

void system_init(void)
{
    uint8_t position = 0U;
    uint8_t valid = 0U;

    Command_Parser_Init();
    Feedback_Processor_Init();
    Motor_Driver_Init();
    LED_Status_Handler_Init();
    Flap_Control_Logic_Init();

    Motor_Driver_Stop();
    LED_Status_Handler_Set_Power_Led(1U);

    Feedback_Processor_Update();
    Feedback_Processor_Get_Position(&position, &valid);
    if (valid != 0U)
    {
        LED_Status_Handler_Set_Led_State(position);
    }
    else
    {
        LED_Status_Handler_Indicate_Error();
    }

    system_init_status = SYSTEM_INIT_DONE;
}

uint8_t system_startup_get_status(void)
{
    return system_init_status;
}
