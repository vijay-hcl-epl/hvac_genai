#include "System Startup/Initialization.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "Flap Control Logic.h"
#include "LED Status Handler.h"
#include "Motor Driver.h"

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
