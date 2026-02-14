#include "UserCmdHandler.h"
#include "FlapCtrl.h"
#include "MotorDriver.h"
#include "PosFeedback.h"
#include "StatusIndication.h"
int main(void) {
    // Init all modules
    MotorDriver_Init();
    PosFeedback_Init();
    StatusIndication_Init();
    FlapCtrl_Init();
    UserCmdHandler_Init();
    // Main loop
    while (1) {
        FlapCtrl_MainLoop();
        // In real, poll UART/interrupt, etc.
    }
    return 0;
}
