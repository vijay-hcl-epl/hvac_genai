#include "System_Startup_Initialization.h"
#include "Command_Parser.h"
#include "Feedback_Processor.h"
#include "Flap_Control_Logic.h"
#include "LED_Status_Handler.h"
#include "Motor_Driver.h"

static uint8_t system_initialized;

void SystemStartupInitialization_Init(void)
{
    FeedbackProcessor_PositionType feedback;

    system_initialized = 0U;

    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControl_Init();
    LEDStatusHandler_Init();
    MotorDriver_Init();
    MotorDriver_StopMotor();

    FeedbackProcessor_Update();
    feedback = FeedbackProcessor_GetPosition();
    if (feedback.valid != 0U)
    {
        LEDStatusHandler_SetLedState(feedback.position);
    }
    else
    {
        MotorDriver_StopMotor();
        LEDStatusHandler_IndicateError();
    }

    system_initialized = 1U;
}

void SystemStartupInitialization_TaskDispatcher(void)
{
    CommandParser_CommandType command;

    CommandParser_Service();
    command = CommandParser_GetLatestCommand();

    if (command.valid != 0U)
    {
        FlapControl_IssueMovementCmd(command.position);
    }

    FlapControl_EvaluateFeedback();
}

uint8_t SystemStartupInitialization_IsInitialized(void)
{
    return system_initialized;
}
