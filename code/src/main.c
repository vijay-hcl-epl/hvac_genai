#include "SystemStartup.h"
#include "FlapControlLogic.h"
#include "FeedbackProcessor.h"

#include "stm32f4xx_hal.h"

int main(void) {
    HAL_Init();
    SystemStartup_Init();
    while (1) {
        FeedbackProcessor_Update();
        FlapControlLogic_Task();
        // Add a small delay or task yield as appropriate
    }
    return 0;
}
