#include "SystemStartup.h"
#include "CommandParser.h"
#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "FeedbackProcessor.h"
#include "LEDStatusHandler.h"

void SystemStartup_Init(void) {
    CommandParser_Init();
    FeedbackProcessor_Init();
    FlapControlLogic_Init();
    LEDStatusHandler_Init();
    MotorDriver_Init();
}
