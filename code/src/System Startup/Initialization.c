#include "System Startup/Initialization.h"
#include "Command Parser.h"
#include "Feedback Processor.h"
#include "Flap Control Logic.h"
#include "LED Status Handler.h"
#include "Motor Driver.h"

static uint8_t system_initialized;

void SystemStartup_Init(void)
{
    FeedbackProcessor_PositionType feedback;

    system_initialized = 0U;
    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControl_Init();
    LedStatusHandler_Init();
    MotorDriver_Init();
    MotorDriver_StopMotor();

    FeedbackProcessor_Update();
    feedback = FeedbackProcessor_GetPosition();
    if (feedback.valid != 0U)
    {
        LedStatusHandler_SetLedState(feedback.position);
        system_initialized = 1U;
    }
    else
    {
        MotorDriver_StopMotor();
        LedStatusHandler_IndicateError();
        system_initialized = 1U;
    }
}

void SystemStartup_TaskDispatcher(void)
{
    uint8_t target_position = 0U;

    (void)CommandParser_PollUart();
    if (CommandParser_GetLatestCommand(&target_position) != 0U)
    {
        FlapControl_IssueMovementCmd(target_position);
    }

    FlapControl_Task();
}

uint8_t SystemStartup_IsInitialized(void)
{
    return system_initialized;
}
