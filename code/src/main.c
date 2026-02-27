#include "command_handler.h"
#include "state_manager.h"
#include "position_sensing.h"
#include "control_logic.h"
#include "motor_driver.h"
#include "status_indication.h"
#include "hw_abstraction.h"
#include "config.h"

int main(void) {
    CommandHandler_Init();
    StateManager_Init();
    PositionSensing_Init();
    ControlLogic_Init();
    MotorDriver_Init();
    StatusIndication_Init();
    // MCU HAL Init/Startup code here

    while (1) {
        // Simulate UART -> Command Handler, should normally be an interrupt or event
        // For prototype/demo, poll for UART RX and inject CommandHandler_ReceiveChar()

        PositionSensing_Update();
        ControlLogic_Process();
        // Status LED blink/heartbeat can be here if desired
    }

    return 0;
}
